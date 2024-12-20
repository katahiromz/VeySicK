%{
    // VeySicK Lexer by katahiromz
    // Copyright (C) 2024 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
    // License: MIT
    #include "ast.h"        // AST (抽象構造木)
    #include "parser.h"     // パーサー (構文解析器)
    #undef NOMINMAX // There was a trouble about std::min and std::max
    #include <cstring>
%}

%option reentrant noyywrap nounput

NEWLINE            (\r?\n|\r)
STRING             \"[^\"\r\n]*\"?
IDENTIFIER         [A-Za-z][A-Za-z0-9\.]*[\$\#\!\%\&]?@?
OCTAL              (&O|&o|&)[0-7]+
HEX                (&H|&h)[0-9A-Fa-f]+
DIGITS             [0-9]+[0-9 \t]*
REAL               ([0-9]+[0-9 \t]*\.[0-9 \t]*|\.[0-9]+[0-9 \t]*)
EXPONENT           ({DIGITS}|{REAL})[ \t]*[eEdD][ \t]*[\-\+]?[0-9]+

%%

REM([ \t]|:).* {
    // Line comment as REM statement
    yylval = std::make_shared<VskAst>(INSN_REM, yytext);
    vsk_target_column += yyleng;
    return TK_COMMENT;
}
'.* {
    // Line comment by apostrophe
    yylval = std::make_shared<VskAst>(INSN_REM, yytext);
    vsk_target_column += yyleng;
    return TK_COMMENT;
}
{NEWLINE} {
    ++vsk_iLine;
    vsk_target_column = 0;
    vsk_in_data = false;
    return TK_NEWLINE;
}
{STRING} {
    // String literal
    VskString str = yytext;
    vsk_unquote(str);
    yylval = std::make_shared<VskAst>(INSN_STR_LITERAL, str);
    vsk_target_column += yyleng;
    return TK_STRING;
}

[^ \t\.,:\r\n"]([^,:\r\n]*[^ \t\.,:\r\n"])? {
    // データ項目かもしれない
    if (!vsk_in_data) // DATA内部でなければ
        REJECT; // 却下

    // これはデータ項目
    VskString str = yytext;
    yylval = vsk_ast(INSN_DATA_LITERAL, str.c_str());
    vsk_target_column += yyleng;
    return TK_STRING;
}

"["     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_L_BRACKET; }
"]"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_R_BRACKET; }
"{"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_L_BRACE; }
"}"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_R_BRACE; }
"("     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_L_PAREN; }
")"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_R_PAREN; }
"+"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_PLUS; }
"-"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_MINUS; }
"*"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_ASTERISK; }
"/"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_SLASH; }
"^"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_HAT; }
"$"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_DOLLAR; }
"~"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_TILDA; }
"|"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_VBAR; }
"\\"    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_BACKSLASH; }
";"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_SEMICOLON; }
":"     { yylval = vsk_ast(); vsk_target_column += yyleng; vsk_in_data = false; return TK_COLON; }
","     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_COMMA; }
"?"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_QUESTION; }
"_"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_UNDERLINE; }
"="     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_EQUAL; }
"<>"    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_NE; }
"><"    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_NE; }
"<="    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_LE; }
"=<"    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_LE; }
">="    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_GE; }
"=>"    { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_GE; }
"<"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_LT; }
">"     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_GT; }
"."     { yylval = vsk_ast(); vsk_target_column += yyleng; return TK_PERIOD; }
"%"     { yylval = vsk_ast(INSN_CINT); vsk_target_column += yyleng; return TK_PERCENT; }
"#"     { yylval = vsk_ast(INSN_CDBL); vsk_target_column += yyleng; return TK_SHARP; }
"!"     { yylval = vsk_ast(INSN_CSNG); vsk_target_column += yyleng; return TK_BANG; }
"&"     { yylval = vsk_ast(INSN_CLNG); vsk_target_column += yyleng; return TK_AMPERSAND; }

{HEX} { // Hexadecimal
    VSK_TYPE type;
    auto ast = vsk_parse_number(yytext, nullptr, type);
    assert(ast);
    assert(ast->is_number());
    yylval = vsk_ast(INSN_CINT, { ast });
    vsk_target_column += yyleng;
    return TK_HEXADECIMAL;
}
{OCTAL} { // Octal
    VSK_TYPE type;
    auto ast = vsk_parse_number(yytext, nullptr, type);
    assert(ast);
    assert(ast->is_number());
    yylval = vsk_ast(INSN_CINT, { ast });
    vsk_target_column += yyleng;
    return TK_OCTAL;
}
{EXPONENT} { // Exponent numeric
    VSK_TYPE type;
    yylval = vsk_parse_number(yytext, nullptr, type);
    assert(yylval);
    assert(yylval->is_number());
    assert(type == VSK_TYPE_SINGLE || type == VSK_TYPE_DOUBLE);
    vsk_target_column += yyleng;
    return TK_FLOATING;
}
{REAL} { // Real numeric
    VSK_TYPE type;
    yylval = vsk_parse_number(yytext, nullptr, type);
    assert(yylval);
    assert(yylval->is_number());
    assert(type == VSK_TYPE_SINGLE || type == VSK_TYPE_DOUBLE);
    vsk_target_column += yyleng;
    return TK_FLOATING;
}
{DIGITS} { // Digits
    VSK_TYPE type;
    yylval = vsk_parse_number(yytext, nullptr, type);
    assert(yylval);
    assert(yylval->is_number());
    return TK_DIGITS;
}

{IDENTIFIER} {
    // Identifier or keyword
    VskString str = yytext;
    vsk_upper(str);
    int token = vsk_token_from_text(yytext);
    if (token == TK_IDENTIFIER)
        yylval = vsk_ast(INSN_IDENTIFIER, str);
    else if (token == TK_FN)
        yylval = vsk_ast(INSN_FN, str);
    else if (token == TK_USR)
        yylval = vsk_ast(INSN_USR, str);
    else
        yylval = vsk_ast(INSN_KEYWORD, str);
    vsk_target_column += yyleng;
    if (str == "DATA")
        vsk_in_data = true;
    return token;
}

[ \t] { // 空白
    vsk_target_column += yyleng;
}

"\x81\x40" { // 全角空白も無視する
    mdbg_traceA("Warning: fullwidth space\n");
    vsk_target_column += yyleng;
}

[\x80-\xFF]+ { // 半角カナなど
    yylval = vsk_ast(INSN_DIRTY_8BIT, yytext);
    vsk_target_column += yyleng;
    return TK_DIRTY_8BIT;
}

"\x01\x02" { // HACK: 式を取得するための特別なコード
    return TK_EVAL;
}

. {
    yylval = vsk_ast(INSN_INVALID_CHARS, yytext);
    vsk_target_column += yyleng;
    return TK_INVALID_CHARS;
}
