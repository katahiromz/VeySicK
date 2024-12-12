#include "VeySicK.h"
#include "draw_algorithm.h"
#include "txt2png.h"
#include <windows.h>
#include <windowsx.h>

////////////////////////////////////////////////////////////////////////////////////

bool vsk_text_to_bitmap(VskTextToPng& text2png)
{
    std::string& text = text2png.m_text;
    if (text.empty())
        return false;

    int max_x = text2png.m_max_x, max_y = text2png.m_max_y;
    int margin = text2png.m_margin;
    int page = text2png.m_page;
    bool is_8801 = text2png.m_is_8801, bold = text2png.m_bold;

    VskImageHandle& hbm = text2png.m_hbm;
    hbm = nullptr;

    const int char_width = (bold ? 9 : 8), char_height = 20;
    int cx = char_width*max_x + 2*margin, cy = char_height*max_y + 2*margin;

    HDC hDC;
    HGDIOBJ hbmOld;
    if (page > 0)
    {
        hbm = (HBITMAP)vsk_create_32bpp_image(cx, cy, nullptr);
        if (!hbm)
            return false;

        hDC = CreateCompatibleDC(NULL);
        hbmOld = SelectObject(hDC, hbm);
        RECT rc = { 0, 0, cx, cy };
        FillRect(hDC, &rc, GetStockBrush(WHITE_BRUSH));
    }

    VskNullPutter null_putter;
    auto black_putter = [&](int x, int y) {
        if (bold) {
            SetPixel(hDC, x, y, RGB(0, 0, 0));
            SetPixel(hDC, x + 1, y, RGB(0, 0, 0));
        } else {
            SetPixel(hDC, x, y, RGB(0, 0, 0));
        }
    };

    Vsk8801AnkGetter getter88;
    Vsk9801AnkGetter getter98;
    auto getter = [&](int x, int y) {
        if (is_8801)
            return getter88(x, y);
        return getter98(x, y);
    };

    int current_page = 1;
    int x = 0, y = 0;
    bool was_lead = false;
    char lead = 0;
    for (auto& ch : text)
    {
        if (x >= max_x)
        {
            x = 0;
            ++y;
        }
        if (was_lead)
        {
            was_lead = false;
            int x0 = margin + char_width*(x - 1), y0 = margin + char_height*y;
            if (vsk_is_sjis_trail(ch))
            {
                VskWord jis = vsk_sjis2jis(lead, ch);
                if (page == current_page)
                    vk_draw_jis(black_putter, null_putter, x0, y0, x0 + 8, y0, jis, false, false);
                ++x;
                continue;
            }
            else
            {
                if (page == current_page)
                    vk_draw_ank(black_putter, null_putter, x0, y0, lead, getter, false, false);
            }
        }
        if (ch == '\r')
            continue;
        if (ch == '\n')
        {
            x = 0;
            ++y;
            if (y >= max_y)
            {
                x = y = 0;
                if (current_page == page && page > 0)
                    break;
                ++current_page;
            }
            continue;
        }

        if (vsk_is_sjis_lead(ch))
        {
            lead = ch;
            was_lead = true;
            ++x;
            continue;
        }

        if (page == current_page)
        {
            int x0 = margin + char_width*x, y0 = margin + char_height*y;
            vk_draw_ank(black_putter, null_putter, x0, y0, ch, getter, false, false);
        }
        ++x;
    }

    if (page <= 0)
    {
        text2png.m_total_pages = current_page;
        return true;
    }

    SelectObject(hDC, hbmOld);
    DeleteDC(hDC);
    return true;
}

#ifdef TXT2PNG_EXE

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

// GDI+用。エンコーダーのCLSIDを取得する
BOOL GetEncoderClsid(CLSID* pClsid, LPCWSTR mime_type)
{
    // エンコーダーのサイズ情報を取得
    UINT cItems = 0, cbEncoders = 0;
    Gdiplus::GetImageEncodersSize(&cItems, &cbEncoders);
    if (!cbEncoders)
        return FALSE; // 失敗

    // エンコーダーを格納するメモリーを確保
    auto pEncoders = (Gdiplus::ImageCodecInfo *)malloc(cbEncoders);
    if (!pEncoders)
        return FALSE; // 失敗

    // エンコーダーを格納
    Gdiplus::GetImageEncoders(cItems, cbEncoders, pEncoders);

    // MIMEの種類に一致するエンコーダーのCLSIDを取得
    for (UINT iItem = 0; iItem < cItems; ++iItem)
    {
        if (wcscmp(pEncoders[iItem].MimeType, mime_type) == 0)
        {
            *pClsid = pEncoders[iItem].Clsid;
            free(pEncoders); // 解放
            return TRUE; // 成功
        }
    }

    free(pEncoders); // 解放
    return FALSE; // 失敗
}

// HBITMAPを画像ファイルとして保存する関数
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCWSTR filename, LPCWSTR mime_type = L"image/png")
{
    // GDI+ BitmapオブジェクトをHBITMAPから作成
    auto bitmap = new Gdiplus::Bitmap(hBitmap, NULL);
    if (!bitmap)
        return FALSE; // 失敗
    std::shared_ptr<Gdiplus::Bitmap> pBitmap(bitmap);

    // PNGエンコーダのCLSIDを取得
    CLSID clsid;
    if (!GetEncoderClsid(&clsid, mime_type))
        return FALSE; // 失敗

    // PNGとして保存
    if (pBitmap->Save(filename, &clsid, NULL) != Gdiplus::Ok)
        return FALSE; // 失敗

    return TRUE; // 成功
}

// スクリーンショットを保存する
bool vsk_save_screenshot(HBITMAP hbm, const char *out_filename)
{
    // GDI+を初期化
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WCHAR szFileW[MAX_PATH];
    ::MultiByteToWideChar(932, 0, out_filename, -1, szFileW, MAX_PATH);
    szFileW[MAX_PATH - 1] = 0;

    // 画像ファイルとして保存
    SaveHBITMAPToFile(hbm, szFileW, L"image/png");

    // GDI+を解放
    Gdiplus::GdiplusShutdown(gdiplusToken);

    // HBITMAPを破棄
    ::DeleteObject(hbm);

    return true;
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        usage();
        return 0;
    }

    std::string input;
    int margin = 16, max_x = 120, max_y = 80;
    bool is_8801 = false;
    bool bold = false;
    for (int iarg = 1; iarg < argc; ++iarg)
    {
        std::string arg = argv[iarg];
        if (arg == "--help")
        {
            usage();
            return 0;
        }
        if (arg == "--version")
        {
            version();
            return 0;
        }
        if (arg == "--margin")
        {
            if (++iarg < argc)
            {
                margin = atoi(argv[iarg]);
            }
            continue;
        }
        if (arg == "--max-x")
        {
            if (++iarg < argc)
            {
                max_x = atoi(argv[iarg]);
            }
            continue;
        }
        if (arg == "--max-y")
        {
            if (++iarg < argc)
            {
                max_y = atoi(argv[iarg]);
            }
            continue;
        }
        if (arg == "--8801")
        {
            is_8801 = true;
            continue;
        }
        if (arg == "--bold")
        {
            bold = true;
            continue;
        }
        if (arg == "-i")
        {
            if (++iarg < argc)
            {
                input = argv[iarg];
            }
            continue;
        }
        fprintf(stderr, "LINE2PNG: Invalid argument '%s'\n", arg.c_str());
        return 1;
    }

    if (input.empty())
    {
        fprintf(stderr, "LINE2PNG: No input file specified\n");
        return 1;
    }

    FILE *fin = fopen(input.c_str(), "rb");
    char buf[256];
    std::string text;
    while (fgets(buf, 256, fin))
    {
        text += buf;
    }
    fclose(fin);

    VskTextToPng text2png;
    text2png.m_text = text;
    text2png.m_max_x = max_x;
    text2png.m_max_y = max_y;
    text2png.m_margin = margin;
    text2png.m_page = 0;
    text2png.m_is_8801 = is_8801;
    text2png.m_bold = bold;
    vsk_text_to_bitmap(text2png);

    int num_pages = text2png.m_total_pages;
    for (int ipage = 1; ipage <= num_pages; ++ipage)
    {
        char out_filename[MAX_PATH];
        std::sprintf(out_filename, "output-%u.png", ipage);

        text2png.m_page = ipage;
        vsk_text_to_bitmap(text2png);
        vsk_save_screenshot(text2png.m_hbm, out_filename);
        DeleteObject(text2png.m_hbm);

        printf("Generated %s.\n", out_filename);
    }

    printf("Total %d pages\n", num_pages);
    return 0;
}

#endif  // def TXT2PNG_EXE
