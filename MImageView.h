#pragma once

#include <windows.h>
#include <windowsx.h>

template <bool t_bOwnImage>
class MImageView
{
public:
    HWND m_hWnd = NULL;
    HBITMAP m_hImage = NULL;

    MImageView()
    {
    }
    virtual ~MImageView()
    {
    }
    void doSubclass(HWND hwnd)
    {
        m_hWnd = hwnd;
        m_fnOldWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
    }
    void doUnSubClass()
    {
        SetWindowLongPtr(m_hWnd, GWLP_USERDATA, 0);
        SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)m_fnOldWndProc);
        m_hWnd = NULL;
    }
    BOOL doRegister()
    {
        WNDCLASS wc = { CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
        wc.lpszClassName = getWndClassName();
        return ::RegisterClass(&wc);
    }
    virtual void setImage(HBITMAP hImage)
    {
        if (t_bOwnImage && m_hImage)
            DeleteObject(m_hImage);
        m_hImage = hImage;
        InvalidateRect(m_hWnd, NULL, TRUE);
    }

    virtual BOOL OnEraseBkgnd(HWND hwnd, HDC hdc)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        HBRUSH hbr = CreateSolidBrush(getBkColor());
        ::FillRect(hdc, &rc, hbr);
        DeleteObject(hbr);
        return TRUE;
    }
    void OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        if (HDC hdc = BeginPaint(hwnd, &ps))
        {
            OnDraw(hwnd, hdc, ps);
            EndPaint(hwnd, &ps);
        }
    }

    double m_zoom_ratio = 1.0;

    bool client_to_image(double& x, double& y)
    {
        if (!m_hWnd || !m_hImage || m_zoom_ratio == 0)
            return false;

        RECT rc;
        GetClientRect(m_hWnd, &rc);

        BITMAP bm;
        GetObject(m_hImage, sizeof(bm), &bm);

        auto ratio = m_zoom_ratio;
        auto center_x = rc.right / 2;
        auto center_y = rc.bottom / 2;
        auto x0 = LONG(center_x - bm.bmWidth * ratio / 2 + 0.5);
        auto y0 = LONG(center_y - bm.bmHeight * ratio / 2 + 0.5);
        auto x1 = x0 + LONG(bm.bmWidth * ratio + 0.5);
        auto y1 = y0 + LONG(bm.bmHeight * ratio + 0.5);

        if (x0 <= x && x <= x1 && y0 <= y && y <= y1)
        {
            x -= x0;
            x /= ratio;
            y -= y0;
            y /= ratio;
            return true;
        }

        return false;
    }

    bool image_to_client(double& x, double& y)
    {
        if (!m_hWnd || !m_hImage || m_zoom_ratio == 0)
            return false;

        RECT rc;
        GetClientRect(m_hWnd, &rc);

        BITMAP bm;
        GetObject(m_hImage, sizeof(bm), &bm);

        auto ratio = m_zoom_ratio;
        auto center_x = rc.right / 2;
        auto center_y = rc.bottom / 2;
        auto x0 = LONG(center_x - bm.bmWidth * ratio / 2 + 0.5);
        auto y0 = LONG(center_y - bm.bmHeight * ratio / 2 + 0.5);
        auto x1 = x0 + LONG(bm.bmWidth * ratio + 0.5);
        auto y1 = y0 + LONG(bm.bmHeight * ratio + 0.5);

        x *= ratio;
        x += x0;
        y *= ratio;
        y += y0;
        POINT pt = { LONG(x), LONG(y) };
        return !!PtInRect(&rc, pt);
    }

    virtual void OnDraw(HWND hwnd, HDC hdc, PAINTSTRUCT& ps)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        BITMAP bm;
        if (!GetObject(m_hImage, sizeof(bm), &bm))
            return;

        HDC hdcMem = CreateCompatibleDC(NULL);
        HGDIOBJ hbmOld = SelectObject(hdcMem, m_hImage);
        assert(hbmOld);

        LONG center_x = rc.right / 2;
        LONG center_y = rc.bottom / 2;

        double ratio1 = bm.bmHeight / (double)bm.bmWidth;
        double ratio2 = rc.bottom / (double)rc.right;
        double ratio;
        if (ratio1 >= ratio2)
            ratio = rc.bottom / (double)bm.bmHeight;
        else
            ratio = rc.right / (double)bm.bmWidth;

        m_zoom_ratio = ratio;

        if (ratio >= 1)
            SetStretchBltMode(hdc, STRETCH_DELETESCANS);
        else
            SetStretchBltMode(hdc, STRETCH_HALFTONE);

        StretchBlt(hdc,
            LONG(center_x - bm.bmWidth * ratio / 2 + 0.5),
            LONG(center_y - bm.bmHeight * ratio / 2 + 0.5),
            LONG(bm.bmWidth * ratio + 0.5),
            LONG(bm.bmHeight * ratio + 0.5),
            hdcMem,
            0, 0, bm.bmWidth, bm.bmHeight,
            SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);
    }

    virtual void OnDestroy(HWND hwnd)
    {
        if (t_bOwnImage)
            DeleteObject(m_hImage);
        m_hImage = NULL;
    }

protected:
    WNDPROC m_fnOldWndProc = NULL;

    virtual LPCTSTR getWndClassName()
    {
        return TEXT("katahiromz MImageView");
    }
    virtual COLORREF getBkColor()
    {
        return GetSysColor(COLOR_3DFACE);
    }

    virtual LRESULT CALLBACK
    DefWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (m_fnOldWndProc)
            return ::CallWindowProc(m_fnOldWndProc, hwnd, uMsg, wParam, lParam);
        return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    virtual LRESULT CALLBACK
    WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            HANDLE_MSG(hwnd, WM_ERASEBKGND, OnEraseBkgnd);
            HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
            HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefWndProc(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }
    static LRESULT CALLBACK
    WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        MImageView *pThis = (MImageView *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (!pThis)
            return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
        return pThis->WndProc(hwnd, uMsg, wParam, lParam);
    }
};
