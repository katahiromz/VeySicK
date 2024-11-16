#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// GDI+用
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0, size = 0;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return 0;
        }
    }

    free(pImageCodecInfo);
    return -1;
}

// HBITMAPをPNGファイルとして保存する関数
bool SaveHBITMAPToPNG(HBITMAP hBitmap, const wchar_t* filename) {
    bool result = false;

    // GDI+ BitmapオブジェクトをHBITMAPから作成
    Bitmap* bitmap = new Bitmap(hBitmap, NULL);
    if (bitmap) {
        CLSID pngClsid;
        // PNGエンコーダのCLSIDを取得
        if (GetEncoderClsid(L"image/png", &pngClsid) == 0) {
            // PNGとして保存
            if (bitmap->Save(filename, &pngClsid, NULL) == Ok) {
                result = true;
            }
        }
        delete bitmap;
    }

    return result;
}

#define JIS_BYTE_START 0x21
#define JIS_BYTE_END   0x7E
#define WIDTH ((JIS_BYTE_END - JIS_BYTE_START) + 1) * 16
#define HEIGHT ((JIS_BYTE_END - JIS_BYTE_START) + 1) * 16

inline uint16_t jis2sjis(uint8_t c0, uint8_t c1)
{
    if (c0 & 0x01)
    {
        c0 >>= 1;
        if (c0 < 0x2F)
            c0 += 0x71;
        else
            c0 -= 0x4F;
        if (c1 > 0x5F)
            c1 += 0x20;
        else
            c1 += 0x1F;
    }
    else
    {
        c0 >>= 1;
        if (c0 < 0x2F)
            c0 += 0x70;
        else
            c0 -= 0x50;
        c1 += 0x7E;
    }

    return MAKEWORD(c1, c0);
}

int main(void)
{
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = WIDTH;
    bmi.bmiHeader.biHeight = HEIGHT;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    HDC hDC = CreateCompatibleDC(NULL);
    LPVOID pvBits;
    HBITMAP hbm = CreateDIBSection(hDC, &bmi, DIB_PAL_COLORS, &pvBits, NULL, 0);
    assert(hbm);

    LOGFONTW lf;
    ZeroMemory(&lf, sizeof(lf));
    lf.lfHeight = -16;
    lf.lfQuality = NONANTIALIASED_QUALITY;
    lstrcpyW(lf.lfFaceName, L"JFドット東雲ゴシック16");
    //lstrcpyW(lf.lfFaceName, L"KHドット小伝馬町16 幾何学的カナ");
    HFONT hFont = CreateFontIndirectW(&lf);

    HGDIOBJ hbmOld = SelectObject(hDC, hbm);
    HGDIOBJ hFontOld = SelectObject(hDC, hFont);

    {
        char buf[LF_FACESIZE];
        GetTextFaceA(hDC, sizeof(buf), buf);
        printf("GetTextFaceA: %s\n", buf);
    }

    SetBkColor(hDC, RGB(255, 255, 255));
    SetTextColor(hDC, 0);
    SetBkMode(hDC, OPAQUE);

    for (int iy = JIS_BYTE_START; iy <= JIS_BYTE_END; ++iy)
    {
        int y = (iy - JIS_BYTE_START) * 16;
        {
            static int s_i = 0;
            if (s_i++ == 0)
            {
                char buf[LF_FACESIZE];
                GetTextFaceA(hDC, sizeof(buf), buf);
                printf("GetTextFaceA: %s\n", buf);
            }
        }
        for (int ix = JIS_BYTE_START; ix <= JIS_BYTE_END; ++ix)
        {
            int x = (ix - JIS_BYTE_START) * 16;
            if (iy == 0x5e)
            {
                WCHAR sz[] = L"沺泛泯泙泪洟衍洶洫洽洸洙洵洳洒洌浣涓浤浚浹浙涎涕濤涅淹渕渊涵淇淦涸淆淬淞淌淨淒淅淺淙淤淕淪淮渭湮渮渙湲湟渾渣湫渫湶湍渟湃渺湎渤滿渝游溂溪溘滉溷滓溽溯滄溲滔滕溏溥滂溟潁漑灌滬滸滾漿滲漱滯漲滌";
                RECT rc = { x, y, x + 16, y + 16 };
                DrawTextW(hDC, &sz[ix - JIS_BYTE_START], 1, &rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOPREFIX);
                continue;
            }
            uint16_t sjis = jis2sjis(iy, ix);

            char buf[3] = { HIBYTE(sjis), LOBYTE(sjis), 0 };
            WCHAR sz[8];
            MultiByteToWideChar(932, 0, buf, -1, sz, 8);
            RECT rc = { x, y, x + 16, y + 16 };
            DrawTextW(hDC, sz, -1, &rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOPREFIX);
        }
    }

    SelectObject(hDC, hbmOld);
    SelectObject(hDC, hFontOld);

    DeleteDC(hDC);
    DeleteObject(hFont);

    if (SaveHBITMAPToPNG(hbm, L"jisrom.png"))
        std::puts("Success!");

    DeleteObject(hbm);
}
