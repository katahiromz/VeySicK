// mdbg.h --- Debugging output -*- C++ -*-
#pragma once

#include <cstdarg>

void mdbg_vprintfA(const char *fmt, va_list va);
void mdbg_vprintfW(const wchar_t *fmt, va_list va);

// デバッグ出力（ANSI版）
void mdbg_printfA(const char *fmt, ...);
// デバッグ出力（Unicode版）
void mdbg_printfW(const wchar_t *fmt, ...);

// デバッグ出力に足跡を残す
#define mdbg_footmark() \
    mdbg_printfA("%s (%d): %s\n", __FILE__, __LINE__, __func__)

// トレース用
#define mdbg_traceA(fmt, ...) \
    mdbg_printfA("%s (%d): " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define mdbg_traceW(fmt, ...) \
    mdbg_printfW(L"%s (%d): " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef UNICODE
    #define mdbg_tprintf mdbg_printfW
    #define mdbg_trace mdbg_traceW
#else
    #define mdbg_tprintf mdbg_printfA
    #define mdbg_trace mdbg_traceA
#endif

// アサート
#include <cassert>
#define mdbg_assert assert
