// print_using.cpp - N88-BASIC PRINT USING emulation in C++11
// License: MIT
// See also: https://github.com/katahiromz/print_using
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ### `PRINT USING` Statement {#print_using}
//
// - **Purpose**: Outputs numbers or strings according to a specified format.
// - **Origin**: Derived from the phrase "Print using"
// - **Syntax**: `PRINT USING` *format_string* `;` *expression* `[`,*expression_separator*,*expression* `]` ...
//
// - **Description**: The *format_string* determines the field width and format for each *expression* output. 
//   While *expression_separator* can be either a comma (`,`) or semicolon (`;`), the separator following 
//   *format_string* must be a semicolon.
//
// **Format options for strings:**
// 
// - `!` … Outputs only the first character of the *expression*.
// - `&    &` … Outputs up to `(n + 2)` characters from *expression*, where `n` is the number of spaces between `&` symbols.
//             If the string is longer than `(n + 2)`, extra characters are discarded; if shorter, it left-aligns 
//             and pads with spaces.
// - `@` … Outputs the *expression* as-is.
//
// **Format options for numbers:**
// 
// - `#` … Specifies the digit count for output by the number of `#` symbols.
// - `.` … Sets the decimal point position.
// - `+` … Outputs the sign before or after the number.
// - `-` … If the number is negative, outputs `-` after the number.
// - `**` … Fills extra space on the left side with `*` characters, occupying two characters.
// - `\\` … Outputs `\` on the left; occupies one character while reserving two characters total.
// - `**\` … Combines `**` and `\\` behaviors, reserving three characters total.
// - `,` … Inserts commas as thousands separators every three digits, occupying one character.
// - `^^^^` … Following `#`, outputs the number in scientific notation.
// - `_` … Escapes the following format character to output it as a literal.
//
// All other characters are output as-is. If the value exceeds the specified width, `%` is displayed instead.
//
// The *format_string* is parsed into segments called "format items" based on established rules. Each format item 
// applies to an expression. If there are fewer expressions than format items, excess format items are ignored. 
// If there are more expressions than format items, the items loop back to the start. When equal, each format item 
// corresponds one-to-one with an expression.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ### `PRINT USING`文 {#print_using}
// 
// - 【機能】 数値や文字列を指定した書式で出力します。
// - 【語源】 Print using
// - 【書式】 `PRINT USING` *書式文字列* `;` *式* `[` *式区切り* *式* `]` ...
// - 【説明】 *書式文字列*によって、*式*の出力される領域や書式を決定します。*式区切り*は、カンマ(`,`)とセミコロン(`;`)のどちらでも変わりませんが、*書式文字列*直後の区切りはセミコロンでなければなりません。
// 
// 文字の書式：
// 
// - `!` … *式*に与えられた文字列の最初の1文字のみを出力します。
// - `&    &` … `&`と`&`の間が`n`個の空白のとき、*式*に与えられた文字列の先頭から`(n + 2)`文字の文字列を出力します。与えられた文字列が`(n + 2)`より長い場合は、余分な文字は無視され、短い場合は、左詰めで出力され、余った部分には空白が出力されます。
// - `@` … *式*に与えられた１つの文字列をそのまま出力します。
// 
// 数値の書式：
// 
// - `#` … 数値の出力する桁の数を`#`の個数で指定します。
// - `.` … 数値の小数点の位置を指定します。
// - `+` … 数値の符号を数値の前か後ろに出力します。
// - `-` … 数値が負の数の場合に、数値の後ろに`-`を出力します。
// - `**` … 数値の左側に余裕がある場合にそこに`*`で埋めて出力します。`**`は2文字分の領域を確保します。
// - `\\` … 数値の左側に`\`を出力します。`**`は2文字分の領域を確保しますが、`\`を出力するのは1文字のみです。
// - `**\` … `**` と `\\` の両方の機能となります。`**\`は3文字分の領域を確保します。
// - `,` … 桁区切りとして3桁ごとにカンマ(`,`)を出力します。`,`は1文字分の領域を確保します。
// - `^^^^` … `#`の後で指定された場合、数値は指数形式で出力されます。
// - `_` … この文字の次にある書式文字を単に文字として出力するのに使います。
// 
// これら以外の文字は、そのまま出力されます。桁数が指定された幅を超えた場合は`%`が出力されます。
// 
// *書式文字列*は、最初にあるルールに従っていくつかの「書式項目（format item）」と呼ばれる部分文字列に分割され、書式項目を単位として処理されます。書式項目の個数が*式*の個数よりも大きいときは、余った*式*は無視されます。書式項目の個数が*式*の個数よりも小さいときは最初の書式項目に戻って順番に循環します。その他のときは、書式項目と*式*は順番に1対1に対応します。
/////////////////////////////////////////////////////////////////////////////

#include "coreapi.h"    // VeySicKのコアAPI

// PRINT USING文の書式の種類
enum VskFormatType {
    UT_UNKNOWN,     // 書式不明
    UT_NUMERIC,     // '+', '-', '#', '.', '*', '\\', ',', '^', '_'
    UT_FIRSTCHAR,   // 最初の文字を出力： '!'
    UT_PARTIALSTR,  // 部分文字列を出力： '&'
    UT_WHOLESTR,    // 文字列全部を出力： '@'
};

// PRINT USING文の書式データ
struct VskFormatItem {
    VskFormatType   m_type = UT_UNKNOWN;            // 書式の種類
    VskString       m_pre;                          // 前に付くテキスト
    VskString       m_text;                         // 実体のテキスト
    VskString       m_post;                         // 後に付くテキスト
    int             m_width = 0;                    // 幅
    int             m_precision = 0;                // 精度
    bool            m_dot = false;                  // ドット（"."）があるか？
    bool            m_asterisk = false;             // "*"か？
#ifdef JAPAN
    bool            m_yen = false;                  // "\\"か？
#else
    bool            m_dollar = false;               // "$"か？
#endif
    bool            m_comma = false;                // ","か？
    bool            m_scientific = false;           // 指数表示（"^^^^"）か？
    bool            m_pre_plus = false;             // 前に付く"+"か？
    bool            m_post_plus = false;            // 後ろに付く"+"か？
    bool            m_post_minus = false;           // 後ろに付く"-"か？
    size_t next_format(const VskString& str, size_t ib0, size_t& ib1);
    size_t parse_string(const VskString& str, size_t ib);
    size_t parse_numeric(const VskString& str, size_t ib);
    VskString format_string(VskString s) const;
    VskString format_numeric(VskDouble d, bool is_double = false) const;
    void clear() { *this = VskFormatItem(); }
};

// 数値文字列にカンマ区切りを追加
VskString vsk_add_commas(const VskString& digits) {
    VskString ret;
    const size_t siz = digits.size();
    for (size_t i = 0; i < siz; ++i) {
        assert('0' <= digits[i] && digits[i] <= '9'); // 数字のみを仮定
        ret += digits[i];
        if ((siz - i > 3) && ((siz - i) % 3 == 1)) {
            ret += ',';
        }
    }
    return ret;
}

#ifndef NDEBUG
// vsk_add_commas関数のテスト
void vsk_add_commas_test() {
    assert(vsk_add_commas("0") == "0");
    assert(vsk_add_commas("100") == "100");
    assert(vsk_add_commas("1000") == "1,000");
    assert(vsk_add_commas("10000") == "10,000");
    assert(vsk_add_commas("1000000") == "1,000,000");
    assert(vsk_add_commas("999999") == "999,999");
}
#endif

// 文字書式をパースする
size_t VskFormatItem::parse_string(const VskString& str, size_t ib) {
    switch (str[ib]) {
    case '&':
        ++ib;
        while (str[ib] == ' ') ++ib;
        if (str[ib] == '&') {
            ++ib;
        }
        break;
    case '@':
    case '!':
        ++ib;
    default:
        break;
    }
    return ib;
}

// 数値書式をパースする
size_t VskFormatItem::parse_numeric(const VskString& str, size_t ib) {
    clear();
    m_type = UT_NUMERIC;
    if (str[ib] == '+') {
        m_pre_plus = true;
        ++m_width;
        ++ib;
    }
#ifdef JAPAN
    if (std::memcmp(&str[ib], "**\\", 3) == 0) {
        m_asterisk = m_yen = true;
        m_width += 3;
        ib += 3;
#else
    if (std::memcmp(&str[ib], "**$", 3) == 0) {
        m_asterisk = m_dollar = true;
        m_width += 3;
        ib += 3;
#endif
    } else if (std::memcmp(&str[ib], "**", 2) == 0) {
        m_asterisk = true;
        m_width += 2;
        ib += 2;
#ifdef JAPAN
    } else if (std::memcmp(&str[ib], "\\\\", 2) == 0) {
        m_yen = true;
        m_width += 2;
        ib += 2;
#else
    } else if (std::memcmp(&str[ib], "$$", 2) == 0) {
        m_dollar = true;
        m_width += 2;
        ib += 2;
#endif
    }
    while (str[ib] == ',' || str[ib] == '#') {
        if (str[ib] == ',') m_comma = true;
        ++m_width;
        ++ib;
    }
    if (str[ib] == '.') { m_dot = true; ++m_width; ++ib; }
    if (m_dot) {
        while (str[ib] == '#') { ++ib; ++m_width; ++m_precision; }
    }
    if (std::memcmp(&str[ib], "^^^^", 4) == 0) {
        m_scientific = true;
        ib += 4;
    }
    if (!m_pre_plus) {
        if (str[ib] == '-') {
            m_post_minus = true;
            ++ib;
        } else if (str[ib] == '+') {
            m_post_plus = true;
            ++ib;
        }
    }
    return ib;
}

// 次の書式
size_t VskFormatItem::next_format(const VskString& str, size_t ib0, size_t& ib1) {
    size_t ib = ib0, ib_save;
    m_type = UT_UNKNOWN;
    bool found = false;

    for (;;) {
        if (str.size() <= ib) {
            if (!found) {
                ib1 = str.size();
                return ib;
            }
            return str.size();
        }
        switch (str[ib]) {
        case '_':
            if (ib + 1 < str.size()) {
                ib += 2;
                continue;
            }
            return str.size();
        case '!':
            if (found) return ib;
            ib1 = ib;
            found = true;
            m_type = UT_FIRSTCHAR;
            ib1 = ib;
            ++ib;
            continue;
        case '&':
            ib_save = ib;
            ++ib;
            while (str[ib] == ' ') ++ib;
            if (str[ib] != '&') {
                continue;
            }
            ++ib;
            if (found) return ib_save;
            ib1 = ib_save;
            found = true;
            m_type = UT_PARTIALSTR;
            continue;
        case '@':
            if (found) return ib;
            ib1 = ib;
            found = true;
            ++ib;
            m_type = UT_WHOLESTR;
            continue;
        case '#':
            if (ib0 < ib && str[ib - 1] == '.') {
                --ib;
            }
            if (ib0 < ib && str[ib - 1] == '+') {
                --ib;
            }
            if (found) return ib;
            ib1 = ib;
            found = true;
            clear();
            ib = parse_numeric(str, ib);
            continue;
#ifdef JAPAN
        case '\\':
            if (std::memcmp(&str[ib], "\\\\", 2) != 0)
#else
        case '$':
            if (std::memcmp(&str[ib], "$$", 2) != 0)
#endif
            {
                ++ib;
                continue;
            }
            if (ib0 < ib && str[ib - 1] == '+') {
                --ib;
            }
            if (found) return ib;
            ib1 = ib;
            found = true;
            clear();
            ib = parse_numeric(str, ib);
            continue;
        case '*':
#ifdef JAPAN
            if (std::memcmp(&str[ib], "**\\", 3) == 0)
#else
            if (std::memcmp(&str[ib], "**$", 3) == 0)
#endif
            {
                if (ib0 < ib && str[ib - 1] == '+') {
                    --ib;
                }
                if (found) return ib;
                ib1 = ib;
                found = true;
                clear();
                ib = parse_numeric(str, ib);
                continue;
            }
            if (std::memcmp(&str[ib], "**", 2) == 0) {
                if (ib0 < ib && str[ib - 1] == '+') {
                    --ib;
                }
                if (found) return ib;
                ib1 = ib;
                found = true;
                clear();
                ib = parse_numeric(str, ib);
                continue;
            }
            ++ib;
            continue;
        default:
            ++ib;
            continue;
        }
    }
}

// PRINT USING文の書式を解析する
bool vsk_parse_formats(std::vector<VskFormatItem>& items, const VskString& str)
{
    items.clear();

    size_t ib0 = 0, ib1, ib2, ib3;
    while (ib0 < str.size()) {
        VskFormatItem item;
        ib2 = item.next_format(str, ib0, ib1);
        if (ib0 == ib2)
            break;
        if (item.m_type == UT_NUMERIC) {
            ib3 = item.parse_numeric(str, ib1);
        } else {
            ib3 = item.parse_string(str, ib1);
        }
        item.m_pre = str.substr(ib0, ib1 - ib0);
        item.m_text = str.substr(ib1, ib3 - ib1);
        item.m_post = str.substr(ib3, ib2 - ib3);
        //printf("'%s' '%s' '%s'\n", item.m_pre.c_str(), item.m_text.c_str(), item.m_post.c_str());
        items.push_back(item);
        ib0 = ib2;
    }

    return !items.empty();
}

#ifndef NDEBUG
// vsk_parse_formats関数のテスト
void vsk_parse_formats_test(void)
{
    std::vector<VskFormatItem> items;
    assert(!vsk_parse_formats(items, ""));

    bool ret = vsk_parse_formats(items, "\n");
    assert(ret);
    assert(items.size() == 1);
    assert(items[0].m_pre == "\n");
    assert(items[0].m_post == "");

    ret = vsk_parse_formats(items, "## ##");
    assert(ret);
    assert(items.size() == 2);
    assert(items[0].m_pre == "");
    assert(items[0].m_text == "##");
    assert(items[0].m_post == " ");
    assert(items[1].m_pre == "");
    assert(items[1].m_text == "##");
    assert(items[1].m_post == "");

    ret = vsk_parse_formats(items, "### & & ###");
    assert(ret);
    assert(items.size() == 3);
    assert(items[0].m_pre == "");
    assert(items[0].m_text == "###");
    assert(items[0].m_post == " ");
    assert(items[1].m_pre == "");
    assert(items[1].m_text == "& &");
    assert(items[1].m_post == " ");
    assert(items[2].m_pre == "");
    assert(items[2].m_text == "###");
    assert(items[2].m_post == "");
}
#endif  // ndef NDEBUG

// 文字列書式を評価する
VskString vsk_format_pre_post(VskString s)
{
    VskString ret;
    for (size_t ib = 0; ib < s.size(); ++ib) {
        if (s[ib] == '_') {
            if (ib + 1 < s.size()) {
                ++ib;
            }
            continue;
        }
        ret += s[ib];
    }
    return ret;
}

// 文字列書式を評価する
VskString VskFormatItem::format_string(VskString s) const
{
    assert(m_type != UT_NUMERIC);

    VskString ret = vsk_format_pre_post(m_pre);

    if (m_text[0] == '@') {
        ret += s;
    } else if (m_text[0] == '!') {
        ret += s[0];
    } else if (m_text[0] == '&') {
        s.resize(m_text.size(), ' ');
        ret += s;
    }

    ret += vsk_format_pre_post(m_post);
    return ret;
}

// 数値書式を評価する
VskString VskFormatItem::format_numeric(VskDouble d, bool is_double) const {
    assert(m_type == UT_NUMERIC);

    // 無効な数値 (NaN; Not a Number)か？
    if (std::isnan(d)) return "NaN";

    // マイナスがあれば覚えておき、絶対値にする
    bool minus = std::signbit(d);
    if (minus) d = -d;

    // 無限大（INFINITY）か？
    if (std::isinf(d)) return minus ? "-INF" : " INF";

    // 指数表示の指数を取得し、指数に合わせる
    int exponent = 0;
    if (m_scientific) {
        if (d <= std::numeric_limits<decltype(d)>::epsilon()) {
            d = 0;
        } else if (d < 1 || d >= 10) {
            exponent = int(std::log10(d));
            d *= std::pow(10, -exponent);
        }
    }

    // 小数部が長すぎないようにする（標準関数でオーバーフローを避けるため）
    int precision = m_precision;
    if (precision > 256 - 2) precision = 256 - 2;

    // 小数部をテキストに
    char buf[256];
    std::sprintf(buf, "%.*f", precision, d - std::floor(d));
    if (std::strcmp(buf, "0") == 0)
        std::strcpy(buf, "0.0");
    if (buf[0] == '1') { // 四捨五入で繰り上がり？
        auto str0 = std::to_string((unsigned long long)d);
        d += 1;
        auto str1 = std::to_string((unsigned long long)d);
        if (str0.size() < str1.size() && m_scientific) {
            ++exponent;
            d /= 10;
        }
        std::strcpy(buf, "0.0");
    }
    assert(buf[0] == '0' && buf[1] == '.');
    VskString decimals = &buf[1];

    // 整数部をテキストに
    VskString digits = std::to_string((unsigned long long)d);

    // 必要ならカンマ(,)を追加
    if (!m_scientific && m_comma) digits = vsk_add_commas(digits);

    // 通貨記号を追加
#ifdef JAPAN
    if (m_yen) digits = '\\' + digits;
#else
    if (m_dollar) digits = '$' + digits;
#endif

    // 符号を追加
    if (m_pre_plus) {
        digits = (minus ? "-" : "+") + digits;
    } else if (!m_post_plus && !m_post_minus) {
        if (minus) {
            digits = "-" + digits;
        }
    }

    VskString ret; // 結果文字列

    // 必要ならば "0"を削る
    int pre_dot = m_width - precision - m_dot;
    if (pre_dot <= 1) {
        if (digits == "-0") digits = "-";
    }
    if (pre_dot == 0) {
        if (digits == "0") digits = "";
    }

    auto diff = m_width - precision - m_dot - int(digits.size());
    if (diff < 0) { // 桁が足りなければ "%"を出力
        ret = "%" + digits;
    } else if (diff > 0) { // 余裕があれば文字で埋める
        if (m_asterisk) {
            ret += VskString(diff, '*') + digits;
        } else {
            ret += VskString(diff, ' ') + digits;
        }
    } else { // その他の場合はそのまま
        ret = digits;
    }

    if (m_dot) { // 小数点があるなら、小数点と小数部を追加
        if (precision > 0) {
            ret += decimals;
        } else {
            ret += '.';
        }
    }

    if (m_scientific) { // 指数表示なら、指数表示を追加
        char buf[16];
        char ch = (is_double ? 'D' : 'E');
        if (exponent < 0) {
            std::sprintf(buf, "%c-%02u", ch, -exponent);
        } else {
            std::sprintf(buf, "%c+%02u", ch, exponent);
        }
        ret += buf;
    }

    // 末尾に符号を追加
    if (m_post_plus) {
        ret += minus ? '-' : '+';
    } else if (m_post_minus) {
        ret += minus ? '-' : ' ';
    }

    // 前後に文字列を追加
    return vsk_format_pre_post(m_pre) + ret + vsk_format_pre_post(m_post);
}

// PRINT USING文をエミュレートする
VskError vsk_PRINT_USING_helper(VskFilePtr file, const VskString& format_text, const VskAstList& args, bool& is_sep)
{
    std::vector<VskFormatItem> items;
    if (!vsk_parse_formats(items, format_text)) {
        return VSK_ERR_BAD_CALL; // Failure
    }

    size_t iParam = 0;
    bool was_sep = true;
    is_sep = true;
    for (size_t iarg = 0; iarg < args.size(); ++iarg)
    {
        is_sep = (args[iarg]->m_insn == INSN_PRINTING_COMMA ||
                  args[iarg]->m_insn == INSN_PRINTING_SEMICOLON);
        if (was_sep == is_sep)
            return VSK_ERR_SYNTAX;

        if (!is_sep)
        {
            auto& item = items[iParam % items.size()];
            auto arg = vsk_eval_ast(args[iarg]);
            if (!arg) {
                return VSK_ERR_BAD_TYPE;
            }

            if (item.m_type == UT_UNKNOWN) {
                file->write_str(item.format_string(""));
            } else if (item.m_type == UT_NUMERIC) {
                if (!arg->is_number()) {
                    return VSK_ERR_BAD_TYPE;
                }
                bool is_double = (arg->m_insn == INSN_DBL_LITERAL);
                file->write_str(item.format_numeric(arg->value(), is_double));
            } else {
                if (!arg->is_str()) {
                    return VSK_ERR_BAD_TYPE;
                }
                file->write_str(item.format_string(arg->m_str));
            }

            ++iParam;
        }

        was_sep = is_sep;
    }

    return VSK_NO_ERROR; // Success
}
