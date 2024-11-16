// AntiRE.h --- Win32 anti-reverse engineering techniques  -*- C++ -*-

#pragma once

#include <windows.h>
#include <intrin.h> // For __cpuid

////////////////////////////////////////////////////////////////////////////////

#if 0 // どこで失敗しているのか確認
    #define ANTIRE_DEBUG(status) MessageBoxA(NULL, status, "AntiRE", MB_ICONERROR)
#else
    #define ANTIRE_DEBUG(status)
#endif

// 逆工学対策のため、特定の条件でExitProcess 関数を使ってプロセスを終了させる

// Detect debugger
inline void AntiRE_DetectDebugger(void)
{
    if (IsDebuggerPresent())
    {
        ANTIRE_DEBUG("Debugger detected using IsDebuggerPresent");
        ExitProcess(0);
    }
}

// Check debug registers
inline void AntiRE_CheckDebugRegs(void)
{
    CONTEXT context;
    ZeroMemory(&context, sizeof(context));
    context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (!GetThreadContext(GetCurrentThread(), &context))
        return;

#if defined(_M_AMD64) || defined(__x86_64__) // For AMD64
    if (context.Dr0 || context.Dr1 || context.Dr2 || context.Dr3)
    {
        ANTIRE_DEBUG("Debugger detected using debug registers (x64)");
        ExitProcess(0);
    }
#elif defined(_M_IX86) || defined(__i386__) // For x86
    if (context.Dr0 || context.Dr1 || context.Dr2 || context.Dr3)
    {
        ANTIRE_DEBUG("Debugger detected using debug registers (x86)");
        ExitProcess(0);
    }
#elif defined(_M_ARM64) || defined(__arm64__) || defined(__aarch64__) // For ARM64
    if (context.Bvr[0] || context.Bvr[1] || context.Bvr[2] || context.Bvr[3])
    {
        ANTIRE_DEBUG("Debugger detected using debug registers (ARM64)");
        ExitProcess(0);
    }
#elif defined(_M_ARM) || defined(__arm__) // For ARM
    if (context.Bvr[0] || context.Bvr[1] || context.Bvr[2] || context.Bvr[3])
    {
        ANTIRE_DEBUG("Debugger detected using debug registers (ARM)");
        ExitProcess(0);
    }
#else
#error Your processor is not supported yet.
#endif
}

// Detect virtual machine (WARNING: License compliant?)
inline void AntiRE_DetectVirtualMachine(void)
{
#if defined(_M_AMD64) || defined(__x86_64__) || defined(_M_IX86) || defined(__i386__)
    // For x86/x64
    int cpuInfo[4] = {0};

    // CPUID instruction for more information
    __cpuid(cpuInfo, 0x80000008);
    if (cpuInfo[2] & 0x10000) { // Virtualization indicator
        ANTIRE_DEBUG("Virtual machine detected using CPUID");
        ExitProcess(0);
    }
#elif defined(_M_ARM64) || defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM) || defined(__arm__)
    // For ARM/ARM64
    char brand[49];
    __asm__ __volatile__ (
        "mrs x0, midr_el1\n\t"
        "str x0, %0"
        : "=m" (brand)
        :
        : "x0"
    );
    if (strstr(brand, "QEMU") != NULL) // Check QEMU emulation
    {
        ANTIRE_DEBUG("Virtual machine detected (QEMU)");
        ExitProcess(0);
    }
#endif
}

// The stop watch. Returns milliseconds
inline DWORD AntiRE_StopWatch(void)
{
    static DWORD s_dwSaveTick = 0;
    DWORD dwNewTick = GetTickCount();
    DWORD dwOldTick = s_dwSaveTick;
    s_dwSaveTick = dwNewTick;
    return dwNewTick - dwOldTick;
}

// Calculate build-specific value
constexpr size_t AntiRE_GetBuildSpecificValue(void)
{
    size_t ich = 0, value = 0xB00B00;
    // ex) "Sep 29 2024"
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    if (__DATE__[ich]) { value += __DATE__[ich++]; value ^= 0xDEADFACE; value *= 0xBADBAD; }
    ich = 0;
    // ex) "19:30:06"
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    if (__TIME__[ich]) { value += __TIME__[ich++]; value ^= 0x0BADFACE; value *= 0xDEADDEAD; }
    value += __LINE__;
    return value;
}

////////////////////////////////////////////////////////////////////////////////
