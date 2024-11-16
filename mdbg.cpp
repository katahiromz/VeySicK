// mdbg.cpp --- Debugging output -*- C++ -*-
#include "mdbg.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <shlwapi.h>
    #include <strsafe.h>
#endif

#include <cstdio>

void mdbg_vprintfA(const char *fmt, va_list va)
{
#ifndef NDEBUG
    #ifdef _WIN32
        char buf[1024];
        #ifdef _STRSAFE_H_INCLUDED_
            StringCchVPrintfA(buf, _countof(buf), fmt, va);
        #else
            wvnsprintfA(buf, _countof(buf), fmt, va);
        #endif
        OutputDebugStringA(buf);
        fputs(buf, stderr);
    #else
        vfprintf(stderr, fmt, va);
    #endif
#endif
}

void mdbg_vprintfW(const wchar_t *fmt, va_list va)
{
#ifndef NDEBUG
    #ifdef _WIN32
        wchar_t buf[1024];
        #ifdef _STRSAFE_H_INCLUDED_
            StringCchVPrintfW(buf, _countof(buf), fmt, va);
        #else
            wvnsprintfW(buf, _countof(buf), fmt, va);
        #endif
        OutputDebugStringW(buf);
        fputws(buf, stderr);
    #else
        vfwprintf(stderr, fmt, va);
    #endif
#endif
}

// デバッグ出力（ANSI版）
void mdbg_printfA(const char *fmt, ...)
{
#ifndef NDEBUG
    va_list va;
    va_start(va, fmt);
    mdbg_vprintfA(fmt, va);
    va_end(va);
#endif
}

// デバッグ出力（Unicode版）
void mdbg_printfW(const wchar_t *fmt, ...)
{
#ifndef NDEBUG
    va_list va;
    va_start(va, fmt);
    mdbg_vprintfW(fmt, va);
    va_end(va);
#endif
}
