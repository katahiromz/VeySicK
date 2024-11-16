#include "encoding.h"

// JIS全角文字をSJIS全角文字に変換
VskWord vsk_jis2sjis(VskByte high, VskByte low)
{
    if (high & 0x01)
    {
        high >>= 1;
        if (high < 0x2F)
            high += 0x71;
        else
            high -= 0x4F;
        if (low > 0x5F)
            low += 0x20;
        else
            low += 0x1F;
    }
    else
    {
        high >>= 1;
        if (high < 0x2F)
            high += 0x70;
        else
            high -= 0x50;
        low += 0x7E;
    }
    return VskWord((high << 8) | low);
}

// SJIS全角文字をJIS全角文字に変換
VskWord vsk_sjis2jis(VskByte high, VskByte low)
{
    high <<= 1;
    if (low < 0x9F)
    {
        if (high < 0x3F)
            high += 0x1F;
        else
            high -= 0x61;
        if (low > 0x7E)
            low -= 0x20;
        else
            low -= 0x1F;
    }
    else
    {
        if (high < 0x3F)
            high += 0x20;
        else
            high -= 0x60;
        low -= 0x7E;
    }
    return ((VskWord(high) << 8) | low);
}

// SJIS文字列をJIS文字列（KI/KO方式）に変換
VskString vsk_sjis2jis(const VskString& sjis)
{
    VskString ret;
    bool was_lead = false, was_zenkaku = false;
    for (size_t ib = 0; ib < sjis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        auto ch0 = sjis[ib];
        auto ch1 = sjis.c_str()[ib + 1];
        if (vsk_is_sjis_code(ch0, ch1))
        {
            VskByte high = ch0, low = ch1;
            auto jis = vsk_sjis2jis(vsk_make_word(low, high));
            assert(vsk_is_jis_code(jis));
            if (!was_zenkaku)
                ret += VSK_JIS_KANJI_IN;
            ret += vsk_high_byte(jis);
            ret += vsk_low_byte(jis);
            was_lead = true;
            was_zenkaku = true;
            continue;
        }
        if (was_zenkaku)
            ret += VSK_JIS_KANJI_OUT;
        ret += ch0;
        was_zenkaku = false;
    }
    if (was_zenkaku)
        ret += VSK_JIS_KANJI_OUT;
    return ret;
}

// JIS文字列（KI/KO方式）をSJIS文字列に変換
VskString vsk_jis2sjis(const VskString& jis, bool kanji_in)
{
    VskString ret;
    bool was_lead = false;
    for (size_t ib = 0; ib < jis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        auto ch0 = jis[ib];
        auto ch1 = jis.c_str()[ib + 1];
        if (ch0 == 0x1B)
        {
            if (ch1 == 0x4B) // Kanji-In
            {
                kanji_in = true;
                was_lead = true;
                continue;
            }
            if (ch1 == 0x48) // Kanji-Out
            {
                kanji_in = false;
                was_lead = true;
                continue;
            }
        }
        if (kanji_in)
        {
            if (vsk_is_jis_byte(ch0) && vsk_is_jis_byte(ch1))
            {
                auto sjis = vsk_jis2sjis(ch0, ch1);
                ret += vsk_high_byte(sjis);
                ret += vsk_low_byte(sjis);
                was_lead = true;
                continue;
            }
        }
        ret += ch0;
    }
    return ret;
}

// 特定の文字種の日本語文字列の文字数を返す。KLEN関数を参照
int vsk_jis_kanji_len(VskString jis, int type)
{
    VskInt ret = 0;
    bool was_lead = false, kanji_in = false;
    for (size_t ib = 0; ib < jis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        if (memcmp(&jis[ib], VSK_JIS_KANJI_IN, 2) == 0) // KI (Kanji-In)か？
        {
            if (type == 0 || type == 5)
                ++ret;
            kanji_in = true;
            was_lead = true;
        }
        if (memcmp(&jis[ib], VSK_JIS_KANJI_OUT, 2) == 0) // KO (Kanji-Out)か？
        {
            if (type == 0 || type == 5)
                ++ret;
            kanji_in = false;
            was_lead = true;
        }
        auto ch0 = jis[ib];
        auto ch1 = jis.c_str()[ib + 1];
        if (vsk_is_jis_2byte_halfwidth_code(ch0, ch1)) // 2バイト系半角文字か？
        {
            if (type == 0 || type == 2 || type == 4)
                ++ret;
            was_lead = true;
            continue;
        }
        if (kanji_in)
        {
            if (vsk_is_jis_byte(ch0) && vsk_is_jis_byte(ch1)) // JISの全角文字か？
            {
                if (type == 0 || type == 2 || type == 3)
                    ++ret;
                was_lead = true;
                continue;
            }
        }
        // おそらくANK文字
        if (type == 0 || type == 1)
            ++ret;
    }

    return ret;
}

// 特定の文字種の日本語文字列の文字数を返す。KLEN関数を参照
int vsk_sjis_kanji_len(VskString sjis, int type)
{
    VskInt ret = 0;
    bool was_lead = false;
    for (size_t ib = 0; ib < sjis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        auto ch0 = sjis[ib], ch1 = sjis.c_str()[ib + 1];
        if (vsk_is_sjis_code(ch0, ch1)) // SJIS全角文字か？
        {
            if (type == 0 || type == 2)
                ++ret;
            was_lead = true;
            continue;
        }
        // おそらくANK文字
        if (type == 0 || type == 1)
            ++ret;
    }
    return ret;
}

// JIS文字列の先頭からの文字数からバイトインデックスに変換
size_t vsk_jis_kpos2ib(VskString jis, size_t kpos, bool *pkanji_in)
{
    bool was_lead = false, kanji_in = false;
    size_t kindex = 0;
    if (!pkanji_in)
        pkanji_in = &kanji_in;
    for (size_t ib = 0; ib < jis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        ++kindex;
        if (kindex == kpos)
            return ib;
        if (memcmp(&jis[ib], VSK_JIS_KANJI_IN, 2) == 0) // KI (Kanji-In)か？
        {
            *pkanji_in = true;
            was_lead = true;
        }
        if (memcmp(&jis[ib], VSK_JIS_KANJI_OUT, 2) == 0) // KO (Kanji-Out)か？
        {
            *pkanji_in = false;
            was_lead = true;
        }
        auto ch0 = jis[ib];
        auto ch1 = jis.c_str()[ib + 1];
        if (vsk_is_jis_2byte_halfwidth_code(ch0, ch1)) // 2バイト系半角文字か？
        {
            was_lead = true;
            continue;
        }
        if (*pkanji_in)
        {
            if (vsk_is_jis_byte(ch0) && vsk_is_jis_byte(ch1)) // JISの全角文字か？
            {
                was_lead = true;
                continue;
            }
        }
        // その他はおそらくANK文字
    }
    return jis.size();
}

// SJIS文字列の先頭からの文字数からバイトインデックスに変換
size_t vsk_sjis_kpos2ib(VskString sjis, size_t kpos)
{
    bool was_lead = false;
    size_t kindex = 0;
    for (size_t ib = 0; ib < sjis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        ++kindex;
        if (kindex == kpos)
            return ib;
        if (vsk_is_sjis_code(sjis[ib], sjis.c_str()[ib + 1])) // SJISの全角文字か？
        {
            was_lead = true;
            continue;
        }
        // その他はおそらくANK文字
    }
    return sjis.size();
}

// KEXT$関数を参照
VskString vsk_sjis_kanji_extract(const VskString& str, bool is_zenkaku)
{
    VskString ret;
    bool was_lead = false;
    for (size_t ib = 0; ib < str.size(); ++ib)
    {
#ifdef JAPAN
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        auto ch0 = str[ib], ch1 = str.c_str()[ib + 1];
        if (vsk_is_sjis_code(ch0, ch1))
        {
            if (is_zenkaku)
            {
                ret += ch0;
                ret += ch1;
            }
            was_lead = true;
            continue;
        }
#endif
        if (!is_zenkaku)
            ret += str[ib];
    }
    return ret;
}

// KTYPE関数を参照
int vsk_jis_ktype(const char *str)
{
    if (!str[0] || !str[1])
        return 0;
    if (memcmp(str, VSK_JIS_KANJI_IN, 2) == 0) // KI (Kanji-In)か？
        return 3;
    if (memcmp(str, VSK_JIS_KANJI_OUT, 2) == 0) // KO (Kanji-Out)か？
        return 4;
    if (vsk_is_jis_2byte_halfwidth_code(str[0], str[1])) // JISの2バイト系半角文字か？
        return 2;
    if (vsk_is_jis_byte(str[0]) && vsk_is_jis_byte(str[1])) // JISの全角文字か？
        return 1;
    return 0;
}

// KTYPE関数を参照
int vsk_sjis_ktype(const char *str)
{
    if (!str[0] || !str[1])
        return 0;
    if (vsk_is_sjis_lead(str[0]) && vsk_is_sjis_trail(str[1])) // SJISの全角文字か？
        return 1;
    return 0;
}

// バイトインデックスからSJIS文字列の先頭文字数に変換
size_t vsk_sjis_ib2kpos(VskString sjis, size_t ib0)
{
    bool was_lead = false;
    size_t kindex = 0;
    for (size_t ib = 0; ib < sjis.size(); ++ib)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        ++kindex;
        if (ib == ib0)
            return kindex;
        if (vsk_is_sjis_code(sjis[ib], sjis.c_str()[ib + 1])) // SJISの全角文字か？
        {
            was_lead = true;
            continue;
        }
        // その他はおそらくANK文字
    }
    return ++kindex;
}
