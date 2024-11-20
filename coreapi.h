#pragma once

#include "VeySicK.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
// INSN_TYPE - 命令の種類

enum INSN_TYPE
{
#define DEFINE_INSN(id, fn, is_stmt) id,
#include "insn.h"
#undef DEFINE_INSN
    MAX_INSN
};

// INSN_INT_LITERAL
#ifndef INSN_INT_LITERAL
    #ifdef INT_IS_32BIT
        #define INSN_INT_LITERAL INSN_LNG_LITERAL
    #else
        #define INSN_INT_LITERAL INSN_SHT_LITERAL
    #endif
#endif

// 命令の種類から命令の名前へ
VskString vsk_insn2name(INSN_TYPE type);

//////////////////////////////////////////////////////////////////////////////

struct YYLTYPE;

//////////////////////////////////////////////////////////////////////////////
// VskAst - 抽象構造木

extern VskLineNo vsk_iLine;
extern VskColumnNo vsk_target_column;
extern VskLineNo vsk_target_line;

struct VskAst;
typedef std::shared_ptr<VskAst> VskAstPtr;
typedef std::deque<VskAstPtr> VskAstList;

struct VskAst : VskObject
{
    VskAst(INSN_TYPE insn = INSN_OTHER);
    VskAst(INSN_TYPE insn, VskShort value);
    VskAst(INSN_TYPE insn, VskLong value);
    VskAst(INSN_TYPE insn, VskSingle value);
    VskAst(INSN_TYPE insn, VskDouble value);
    VskAst(INSN_TYPE insn, const VskString& str);
    VskAst(INSN_TYPE insn, std::initializer_list<VskAstPtr> children);
    virtual ~VskAst() { }

    VskAstList m_children;

    VskAstList& children() {
        return m_children;
    }
    const VskAstList& children() const {
        return m_children;
    }

    // std::vectorのようにアクセスできるようにする
    bool empty() const {
        return m_children.empty();
    }
    size_t size() const {
        return m_children.size();
    }
    void push_back(VskAstPtr ptr) {
        m_children.push_back(ptr);
    }
    VskAstPtr& operator[](size_t index) {
        return at(index);
    }
    const VskAstPtr& operator[](size_t index) const {
        return at(index);
    }
    VskAstPtr& at(size_t index) {
        assert(index < size());
        return m_children[index];
    }
    const VskAstPtr& at(size_t index) const {
        assert(index < size());
        return m_children[index];
    }
    VskAstList::iterator begin() { return m_children.begin(); }
    VskAstList::iterator end() { return m_children.end(); }
    VskAstList::const_iterator begin() const { return m_children.begin(); }
    VskAstList::const_iterator end() const { return m_children.end(); }
    void insert(VskAstList::iterator it, VskAstPtr item) {
        m_children.insert(it, item);
    }
    template <typename T_ITERATOR>
    void insert(VskAstList::iterator it, T_ITERATOR first, T_ITERATOR last) {
        m_children.insert(it, first, last);
    }

    INSN_TYPE m_insn = INSN_NONE;
    std::string m_str;
    union
    {
        VskDouble m_dbl;
        VskSingle m_sng;
        VskDword m_dwd;
        VskLong m_lng;
        VskWord m_wrd;
        VskShort m_sht;
        VskInt m_int;
    };
    VskLineNo m_program_line = -1;
    VskColumnNo m_column = -1;

    VskString to_str() const;
    VskString to_debug_str();
    bool is_int() const { return m_insn == INSN_INT_LITERAL; }
    bool is_lng() const { return m_insn == INSN_LNG_LITERAL; }
    bool is_integer() const { return is_int() || is_lng(); }
    bool is_sng() const { return m_insn == INSN_SNG_LITERAL; }
    bool is_dbl() const { return m_insn == INSN_DBL_LITERAL; }
    bool is_str() const { return m_insn == INSN_STR_LITERAL; }
    bool is_multi() const { return m_insn == INSN_MULTI; }
    bool is_floating() const { return is_dbl() || is_sng(); }
    bool is_number() const;
    bool is_negative() const;
    bool is_ident() const { return m_insn == INSN_IDENTIFIER; }
    bool is_keyword() const { return m_insn == INSN_KEYWORD; }
    bool is_if_then() const { return m_insn == INSN_IF; }
    bool is_data() const { return m_insn == INSN_DATA; }
    bool is_data_entry() const;
    bool is_data_literal() const { return m_insn == INSN_DATA_LITERAL; }
    bool is_stmt() const;

    const char *c_str() const { return m_str.c_str(); }
    int compare(const VskAst *other) const;
    VskDouble value() const;
    void set_column();
    void copy_node(VskAst *src);
    VskAstPtr substitute(VskAstPtr var, VskAstPtr value);
};

inline VskAstPtr
vsk_ast(INSN_TYPE insn = INSN_OTHER)
{
    auto ret = std::make_shared<VskAst>(insn);
    if (vsk_machine->had_error())
        return nullptr;
    return ret;
}
template <typename T_TYPE>
inline VskAstPtr
vsk_ast(INSN_TYPE insn, const T_TYPE& value)
{
    auto ret = std::make_shared<VskAst>(insn, value);
    if (vsk_machine->had_error())
        return nullptr;
    return ret;
}
inline VskAstPtr
vsk_ast(INSN_TYPE insn, std::initializer_list<VskAstPtr> children)
{
    auto ret = std::make_shared<VskAst>(insn, children);
    if (vsk_machine->had_error())
        return nullptr;
    return ret;
}

// 値からASTを作る
inline VskAstPtr
vsk_ast_sht(VskShort value)
{
    return vsk_ast(INSN_SHT_LITERAL, value);
}
inline VskAstPtr
vsk_ast_lng(VskLong value)
{
    return vsk_ast(INSN_LNG_LITERAL, value);
}
inline VskAstPtr
vsk_ast_sng(VskSingle value)
{
    return vsk_ast(INSN_SNG_LITERAL, value);
}
inline VskAstPtr
vsk_ast_dbl(VskDouble value)
{
    return vsk_ast(INSN_DBL_LITERAL, value);
}
inline VskAstPtr
vsk_ast_str(const VskString& value)
{
    return vsk_ast(INSN_STR_LITERAL, value);
}
inline VskAstPtr
vsk_ast_goto(VskAstPtr line_number)
{
    return vsk_ast(INSN_GOTO, { line_number });
}
#ifdef INT_IS_32BIT
    #define vsk_ast_int vsk_ast_lng
#else
    #define vsk_ast_int vsk_ast_sht
#endif

// 文字列を型付きの数値にする
VskAstPtr vsk_ast_digits(const char *text, int base = 10);
VskAstPtr vsk_ast_exponent(const char *text);
VskAstPtr vsk_ast_real(const char *text);

// マルチステートメントにする
VskAstPtr vsk_ast_multi(VskAstPtr x);
VskAstPtr vsk_ast_multi(VskAstPtr x, VskAstPtr y);
VskAstPtr vsk_ast_multi(VskAstPtr x, VskAstPtr y, VskAstPtr z);

// 符号あり16ビット整数を取得する
bool vsk_sht(VskInt& value, VskAstPtr arg);
// 符号なし16ビット整数を取得する
bool vsk_wrd(VskWord& value, VskAstPtr arg);
// 32ビット整数を取得する
bool vsk_lng(VskLong& value, VskAstPtr arg);
// 単精度型を取得する
bool vsk_sng(VskSingle& value, VskAstPtr arg);
// 倍精度型を取得する
bool vsk_dbl(VskDouble& value, VskAstPtr arg);
// 浮動小数点数を取得する
bool vsk_flt(VskFloat& value, VskAstPtr arg);
// 文字列型を取得する
bool vsk_str(VskString& value, VskAstPtr arg);

#ifdef INT_IS_32BIT
    #define vsk_int vsk_lng
#else
    #define vsk_int vsk_sht
#endif

#ifdef FLOAT_IS_DOUBLE
    #define vsk_flt vsk_dbl
#else
    #define vsk_flt vsk_sng
#endif

//////////////////////////////////////////////////////////////////////////////
// YYSTYPE

#define YYSTYPE VskAstPtr

//////////////////////////////////////////////////////////////////////////////
// VeySicK の字句解析

typedef void *yyscan_t;

int vsk_token_from_text(const char *text);
VskAstPtr vsk_value_from_string(VskString str);

extern "C" int isatty(int);

extern bool vsk_in_data;

void vsk_targeting(VskAstPtr ast);

//////////////////////////////////////////////////////////////////////////////
// VeySicK の構文解析

typedef VskAstPtr VskParseResult;

int yyparse(VskParseResult& result, yyscan_t yyscanner);
void yyerror(VskParseResult& result, yyscan_t yyscanner, const char *s);

#include "parser.h"

// 実際に構文解析を行う関数
VskError vsk_parse_line(const VskString& text, VskParseResult& result);
// 実際に構文解析を行う関数
VskError vsk_parse_program(VskString text, VskParseResult& result);

//////////////////////////////////////////////////////////////////////////////
// VeySicK の意味解析

// 評価を行う関数
VskAstPtr vsk_eval_ast(VskAstPtr arg);
// テキストの評価を行う関数
VskAstPtr vsk_eval_text(const VskString& text);

//////////////////////////////////////////////////////////////////////////////

// 左辺値への入力
bool vsk_complete_lvalue_input(VskAstPtr lvalue, const VskString& data, bool prompt);
// 入力テキストを分割する
void vsk_split_input_text(std::vector<VskString>& data, const VskString& text);
// 左辺値（lvalue）を最適化する
VskAstPtr vsk_lvalue_optimize(VskAstPtr& lvalue, int base);
