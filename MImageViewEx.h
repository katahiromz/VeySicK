#pragma once

#include "MImageView.h"

template <bool t_double_buffer>
class MImageViewEx : public MImageView<false>
{
public:
	MImageViewEx()
    {
        m_hbrChecker = CreateCheckerboardBrush(RGB(225, 225, 225), RGB(150, 150, 150), 4);
    }
	virtual ~MImageViewEx()
    {
        ::DeleteObject(m_hbrChecker);
        ::DeleteObject(m_hbmOffScreen);
    }

    void SetBorderColor(COLORREF border)
    {
        ::DeleteObject(m_hbrChecker);
        if (border == CLR_INVALID)
            m_hbrChecker = CreateCheckerboardBrush(RGB(225, 225, 225), RGB(150, 150, 150), 4);
        else
            m_hbrChecker = ::CreateSolidBrush(border);
    }

    BOOL OnEraseBkgnd(HWND hwnd, HDC hdc) override
    {
        if (!t_double_buffer)
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            ::FillRect(hdc, &rc, m_hbrChecker);
        }
        return TRUE;
    }
    void OnDraw(HWND hwnd, HDC hdc, PAINTSTRUCT& ps) override
    {
        if (!t_double_buffer)
            return MImageView<false>::OnDraw(hwnd, hdc, ps);

        RECT rc;
        GetClientRect(hwnd, &rc);

        HDC hMemDC = CreateCompatibleDC(hdc);
        if (!m_hbmOffScreen || m_cxOffScreen < rc.right || m_cyOffScreen < rc.bottom)
        {
            if (m_hbmOffScreen)
                DeleteObject(m_hbmOffScreen);

            m_hbmOffScreen = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
            m_cxOffScreen = rc.right;
            m_cyOffScreen = rc.bottom;
        }

        HGDIOBJ hbmOld = SelectObject(hMemDC, m_hbmOffScreen);
        ::FillRect(hMemDC, &rc, m_hbrChecker);
        MImageView<false>::OnDraw(hwnd, hMemDC, ps);
        BitBlt(hdc, 0, 0, rc.right, rc.bottom, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, hbmOld);
        DeleteDC(hMemDC);
    }

protected:
    HBRUSH m_hbrChecker = NULL;
    HBITMAP m_hbmOffScreen = NULL;
    INT m_cxOffScreen = 0;
    INT m_cyOffScreen = 0;

    HBRUSH CreateCheckerboardBrush(COLORREF lightColor, COLORREF darkColor, int squareSize)
    {
        HDC hdcMem = CreateCompatibleDC(NULL);
        HBITMAP hbmp = CreateCompatibleBitmap(GetDC(NULL), squareSize * 2, squareSize * 2);
        HBRUSH hbrush = NULL;

        if (hdcMem && hbmp)
        {
            SelectObject(hdcMem, hbmp);

            HBRUSH hbrLight = CreateSolidBrush(lightColor);
            HBRUSH hbrDark = CreateSolidBrush(darkColor);

            RECT rect = { 0, 0, squareSize, squareSize };
            FillRect(hdcMem, &rect, hbrLight);

            rect = { squareSize, 0, squareSize * 2, squareSize };
            FillRect(hdcMem, &rect, hbrDark);

            rect = { 0, squareSize, squareSize, squareSize * 2 };
            FillRect(hdcMem, &rect, hbrDark);

            rect = { squareSize, squareSize, squareSize * 2, squareSize * 2 };
            FillRect(hdcMem, &rect, hbrLight);

            DeleteObject(hbrLight);
            DeleteObject(hbrDark);

            hbrush = CreatePatternBrush(hbmp);
        }

        if (hbmp) DeleteObject(hbmp);
        if (hdcMem) DeleteDC(hdcMem);

        return hbrush;
    }
};
