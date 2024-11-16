// types.h --- VeySick basic types

#pragma once

#define _CRT_SECURE_NO_WARNINGS // Visual C++におけるfopenなどの警告を無視する
#define _USE_MATH_DEFINES // Visual C++でも円周率定数 M_PI を使いたい

#include <vector>           // For std::vector
#include <map>              // For std::map
#include <unordered_map>    // For std::unordered_map
#include <string>           // For std::string and std::wstring
#include <memory>           // For std::shared_ptr and std::make_shared
#include <cstring>          // For std::strlen std::memcpy etc.
#include <cassert>          // For assert macro
#include <cstdint>          // For uint8_t, uint16_t etc.
#include <cmath>            // For Math
#include <deque>            // For std::deque
#include <set>              // For std::set

//////////////////////////////////////////////////////////////////////////////
// VeySicK 基本型

// 基本型の定義
typedef   std::int8_t VskChar;
typedef  std::uint8_t VskByte;
typedef  std::int16_t VskShort;
typedef std::uint16_t VskWord;
typedef  std::int32_t VskLong;
typedef std::uint32_t VskDword, VskDWord;
typedef float  VskSingle;
typedef double VskDouble;

// サイズを確かめる
static_assert(sizeof(VskChar)   == 1, "");
static_assert(sizeof(VskByte)   == 1, "");
static_assert(sizeof(VskShort)  == 2, "");
static_assert(sizeof(VskWord)   == 2, "");
static_assert(sizeof(VskLong)   == 4, "");
static_assert(sizeof(VskDword)  == 4, "");
static_assert(sizeof(VskSingle) == 4, "");
static_assert(sizeof(VskDouble) == 8, "");

#if defined(INT_IS_32BIT) && !defined(ENABLE_LONG)
    #define ENABLE_LONG
#endif

// VskIntとVskFloatは切り替え可能
#ifdef INT_IS_32BIT
    typedef  std::int32_t VskInt;
#else
    typedef  std::int16_t VskInt;
#endif
#ifdef FLOAT_IS_DOUBLE
    typedef double VskFloat;
#else
    typedef float VskFloat;
#endif

// 型を表す文字
typedef VskByte VskType;
enum VSK_TYPE : uint8_t
{
    VSK_TYPE_SINGLE  = '!',
    VSK_TYPE_DOUBLE  = '#',
    VSK_TYPE_INTEGER = '%',
    VSK_TYPE_STRING  = '$',
#ifdef ENABLE_LONG
    VSK_TYPE_LONG    = '&',
#endif
    VSK_TYPE_ARRAY   = '@',
};

typedef VskDouble VskLineNo;        // 行番号
typedef VskDouble VskColumnNo;      // 桁番号

typedef std::string    VskString;   // ANSI文字列
typedef std::wstring   VskWString;  // ワイド文字列
#ifdef UNICODE
    typedef VskWString VskTString;  // テキスト文字列
#else
    typedef VskString  VskTString;  // テキスト文字列
#endif

typedef std::size_t     VskAddr;     // アドレス（符号なし）
typedef std::ptrdiff_t  VskPtrDiff;  // ポインタの差（符号付き）
typedef std::size_t     VskMemSize;  // メモリーサイズ（符号なし）

// 値の小数点以下を四捨五入して丸める
inline VskShort vsk_round(VskShort value)
{
    return value;
}
inline VskLong vsk_round(VskLong value)
{
    return value;
}
inline VskInt vsk_round(VskSingle value)
{
    return VskInt(std::round(value));
}
inline VskInt vsk_round(VskDouble value)
{
    return VskInt(std::round(value));
}

//////////////////////////////////////////////////////////////////////////////
// 正常性チェック

#if defined(UNICODE) != defined(_UNICODE)
    #error
#endif

//////////////////////////////////////////////////////////////////////////////
// _countof

#ifndef _countof
    #define _countof(array) (sizeof(array) / sizeof(array[0]))
#endif

//////////////////////////////////////////////////////////////////////////////
// 抽象オブジェクト クラス

struct VskObject
{
    static long s_cAliveObjects; // オブジェクトの生存数を管理する

    VskObject();
    virtual ~VskObject();
};

//////////////////////////////////////////////////////////////////////////////
// インデックスリスト

typedef size_t VskIndex;
typedef std::deque<VskIndex> VskIndexList;

//////////////////////////////////////////////////////////////////////////////
