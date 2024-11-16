#include "types.h"
#include "sound.h"
#include "encoding.h"
#include "coreapi.h"
#include "mem.h"
#include <cstdio>
#include <memory>   // for std::shared_ptr

#include "freealut/include/AL/alut.h"
#include "fmgon/soundplayer.h"

struct VskScanner
{
    VskString   m_str;
    size_t      m_i;

    VskScanner(const VskString& str, size_t i = 0) : m_str(str), m_i(i) { }

    bool eof() const {
        return (m_i >= m_str.size());
    }
    char peek() const {
        if (!eof()) {
            return m_str[m_i];
        }
        return 0;
    }
    char getch() {
        if (!eof()) {
            char ret = m_str[m_i++];
            return ret;
        }
        return 0;
    }
    void ungetch() {
        if (m_i > 0) {
            --m_i;
        }
    }
}; // struct VskScanner

//////////////////////////////////////////////////////////////////////////////

#define VSK_MAX_CHANNEL 6

std::shared_ptr<VskSoundPlayer> vsk_sound_player;
VskSoundSetting                 vsk_fm_sound_settings[VSK_MAX_CHANNEL];
VskSoundSetting                 vsk_ssg_sound_settings[VSK_MAX_CHANNEL];

//////////////////////////////////////////////////////////////////////////////
// VskSingItem --- CMD SING 用の演奏項目

struct VskSingItem
{
    VskString               m_subcommand;
    VskString               m_param;
    char                    m_sign;
    bool                    m_dot;

    VskSingItem() { clear(); }

    void clear() {
        m_subcommand.clear();
        m_param.clear();
        m_sign = 0;
        m_dot = false;
    }
};

VskAstPtr vsk_get_sing_param(const VskSingItem& item)
{
    if (item.m_param.empty())
        return nullptr;
    return vsk_eval_text(item.m_param);
} // vsk_get_sing_param

bool vsk_phrase_from_sing_items(
    std::shared_ptr<VskPhrase> phrase,
    const std::vector<VskSingItem>& items)
{
    float length;
    for (auto& item : items) {
        char ch = item.m_subcommand[0];
        switch (ch) {
        case 'T':
            // テンポ
            if (auto ast = vsk_get_sing_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((48 <= i0) && (i0 <= 255)) {
                    phrase->m_setting.m_tempo = i0;
                    continue;
                }
            }
            return false;
        case 'O':
            // オクターブ
            if (auto ast = vsk_get_sing_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((3 <= i0) && (i0 <= 6)) {
                    phrase->m_setting.m_octave = i0 - 1;
                    continue;
                }
            }
            return false;
        case 'L':
            // 音符・休符の長さ
            if (auto ast = vsk_get_sing_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((1 <= i0) && (i0 <= 32)) {
                    phrase->m_setting.m_length = (24.0f * 4.0f) / i0;
                    continue;
                }
            }
            return false;
        case 'C': case 'D': case 'E': case 'F': case 'G': case 'A': case 'B':
        case 'R':
            // 音符か休符
            if (auto ast = vsk_get_sing_param(item)) {
                auto L = ast->value();
                // NOTE: 24 is the length of a quarter note
                if ((1 <= L) && (L <= 32)) {
                    length = float(24 * 4 / L);
                } else {
                    return false;
                }
            } else {
                length = phrase->m_setting.m_length;
            }
            phrase->add_note(ch, item.m_dot, length, item.m_sign);
            continue;
        case 'X':
            // 画面表示
            break;
        }
    }
    return true;
} // vsk_phrase_from_sing_items

bool vsk_expand_sing_items(std::vector<VskSingItem>& items)
{
retry:;
    size_t k = VskString::npos;
    int level = 0, repeat = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].m_subcommand == "RP") {
            // TODO:
            repeat = 1;
        }
        if (items[i].m_subcommand == "[") {
            k = i;
            ++level;
        }
        if (items[i].m_subcommand == "]") {
            --level;
            if ((level == 0) && (repeat != 0)) {
                std::vector<VskSingItem> sub(items.begin() + k + 1, items.begin() + i);
                std::vector<VskSingItem> children;
                for (int m = 0; m < repeat; ++m) {
                    children.insert(children.end(), sub.begin(), sub.end());
                }
                items.erase(items.begin() + k, items.begin() + i + 1);
                items.insert(items.begin() + k, children.begin(), children.end());
                goto retry;
            }
        }
    }
    return true;
} // vsk_expand_sing_items

bool vsk_eval_sing_items(
    std::vector<VskSingItem>& items, 
    const VskString& expr)
{
    VskScanner scanner(expr);
    items.clear();

    VskSingItem item;
    VskString subcommand;
    while (!scanner.eof()) {
        char ch = vsk_toupper(scanner.getch());
        if (vsk_isblank(ch)) {
            continue;
        }
        if (ch == ';') {
            continue;
        }
        if (ch == '[') {
            item.m_subcommand = "[";
            items.push_back(item);
            item.clear();
            continue;
        }
        if (ch == ']') {
            item.m_subcommand = "]";
            items.push_back(item);
            item.clear();
            continue;
        }
        int status = 0;
        if (vsk_isupper(ch)) {
            subcommand.push_back(ch);
            if (subcommand.size() == 1) {
                switch (subcommand[0]) {
                case 'T': case 'O': case 'L': 
                case 'C': case 'D': case 'E': case 'F': case 'G': case 'A': case 'B':
                case 'X':
                    status = 1;
                    break;
                case 'R':
                    status = 1;
                    if (scanner.peek() == 'P') {
                        subcommand += scanner.getch();
                    }
                    break;
                default:
                    break;
                }
            } else {
                continue;
            }
        }
        if (status == 0) {
            // Illegal function call
            return false;
        }
        item.m_subcommand = subcommand;
        subcommand.clear();
        if (scanner.peek() == '(') {
            scanner.getch();
            for (;;) {
                ch = scanner.peek();
                if ((ch == ')') || (ch == 0)) {
                    continue;
                }
                scanner.getch();
                if (!vsk_isblank(ch)) {
                    item.m_param.push_back(ch);
                }
            }
        } else {
            ch = scanner.peek();
            if ((ch == '+') || (ch == '#') || (ch == '-')) {
                item.m_sign = scanner.getch();
                ch = scanner.peek();
            }
            if (vsk_isdigit(ch)) {
                while (!scanner.eof()) {
                    ch = scanner.getch();
                    if (!vsk_isdigit(ch)) {
                        break;
                    }
                    item.m_param.push_back(ch);
                }
                if (!scanner.eof()) {
                    scanner.ungetch();
                }
            }
            ch = scanner.peek();
            if (ch == '.') {
                item.m_dot = true;
                scanner.getch();
            }
        }
        items.push_back(item);
        item.clear();
    }

    return vsk_expand_sing_items(items);
} // vsk_eval_sing_items

// CMD SING文実装の本体
bool vsk_sound_sing(const VskString& str)
{
    std::vector<VskSingItem> items;
    if (!vsk_eval_sing_items(items, str))
        return false;

    // create phrase
    auto phrase = std::make_shared<VskPhrase>();
    phrase->m_setting = vsk_ssg_sound_settings[0];
    phrase->m_setting.m_fm = false;
    if (!vsk_phrase_from_sing_items(phrase, items))
        return false;

    VskScoreBlock block = { phrase };
    vsk_sound_player->play(block);
    vsk_ssg_sound_settings[0] = phrase->m_setting;
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// VskPlayItem --- CMD PLAY 用の演奏項目

struct VskPlayItem
{
    VskString               m_subcommand;
    VskString               m_param;
    VskString               m_param2;
    char                    m_sign;     // +, -, #
    bool                    m_dot;      // .
    bool                    m_and;      // &
    int                     m_plet_count;
    int                     m_plet_L;

    VskPlayItem() { clear(); }

    void clear() {
        m_subcommand.clear();
        m_param.clear();
        m_param2.clear();
        m_sign = 0;
        m_dot = false;
        m_and = false;
        m_plet_count = 1;
        m_plet_L = 0;
    }
};

// 演奏項目を再スキャン (Pass 2)
bool vsk_rescan_play_items(std::vector<VskPlayItem>& items)
{
    size_t k = VskString::npos;
    int level = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].m_subcommand == "{") {
            k = i;
            ++level;
        }
        if (items[i].m_subcommand == "}") {
            --level;
            if (level == 0) {
                int plet_count = int(i - (k + 1));
                int plet_L = atoi(items[i].m_param.c_str());
                for (size_t m = k + 1; m < i; ++m) {
                    items[m].m_plet_count = plet_count;
                    items[m].m_plet_L = plet_L;
                }
                items.erase(items.begin() + i);
                items.erase(items.begin() + k);
                --i;
            }
        }
    }
    return true;
} // vsk_rescan_play_items

// 演奏項目をスキャン (Pass 1)
bool vsk_scan_play_param(const char *& pch, VskPlayItem& item)
{
    while (vsk_isblank(*pch)) ++pch;

    if (vsk_isdigit(*pch)) {
        for (;; pch++) {
            if (vsk_isblank(*pch))
                continue;
            if (!vsk_isdigit(*pch))
                break;
            item.m_param += *pch;
        }
    } else if (*pch == '=') {
        for (++pch; *pch && *pch != ';'; ++pch) {
            if (!vsk_isblank(*pch))
                item.m_param += *pch;
        }

        if (!*pch)
            return false;
        ++pch;
    }

    return true;
} // vsk_scan_play_param

// 演奏項目を評価する
bool vsk_eval_play_items(std::vector<VskPlayItem>& items, const VskString& expr)
{
    const char *pch = expr.c_str();
    items.clear();

    // MMLのパース
    VskPlayItem item;
    while (*pch != 0) {
        char ch = vsk_toupper(*pch++);
        if (ch == 0)
            break;
        if (vsk_isblank(ch))
            continue;
        switch (ch) {
        case ' ': case '\t': // blank
            continue;
        case '!': case '*':
            // TODO: LFO効果
            continue;
        case '_':
            // TODO: 移調
            continue;
        case '&': case '^':
            // タイ
            if (items.size()) {
                items.back().m_and = true;
            }
            continue;
        case '<': case '>':
            // オクターブを増減する
            item.m_subcommand = {ch};
            break;
        case '{':
            // 繰り返し始め
            item.m_subcommand = {ch};
            break;
        case '}':
            // 繰り返し終わり
            item.m_subcommand = {ch};
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            break;
        case 'Y': case ',':
            // OPNレジスタ
            item.m_subcommand = {ch};
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            break;
        case 'P': case 'R':
            // 休符
            if (ch == 'P') ch = 'R';
            item.m_subcommand = {ch};
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            // 付点
            if (*pch == '.') {
                item.m_dot = true;
                ++pch;
            }
            break;
        case 'N': case 'K':
            // 指定された高さの音
            if (ch == 'K') ch = 'N';
            item.m_subcommand = {ch};
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            // 付点
            if (*pch == '.') {
                item.m_dot = true;
                ++pch;
            }
            break;
        case 'C': case 'D': case 'E': case 'F': case 'G': case 'A': case 'B':
            // 音符
            item.m_subcommand = {ch};
            while (vsk_isblank(*pch)) ++pch;
            // シャープとフラット
            switch (*pch) {
            case '-': case '#': case '+':
                item.m_sign = *pch++;
                break;
            }
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            // 付点
            if (*pch == '.') {
                item.m_dot = true;
                ++pch;
            }
            break;
        case '@':
            ch = vsk_toupper(*pch++);
            switch (ch) {
            case 'V': case 'W':
                // "@V", "@W"
                item.m_subcommand = {'@', ch};
                // パラメータ
                if (!vsk_scan_play_param(pch, item))
                    return false;
                break;
            default:
                // "@": 音色を変える
                --pch;
                item.m_subcommand = "@";
                // パラメータ
                if (!vsk_scan_play_param(pch, item))
                    return false;
                break;
            }
            break;
        case 'M': case 'S': case 'V': case 'L': case 'Q':
        case 'O': case 'T': case 'Z':
            // その他のMML
            item.m_subcommand = {ch};
            // パラメータ
            if (!vsk_scan_play_param(pch, item))
                return false;
            break;
        default:
            return false;
        }
        items.push_back(item);
        item.clear();
    }

    return vsk_rescan_play_items(items);
} // vsk_eval_play_items

VskAstPtr vsk_get_play_param(const VskPlayItem& item)
{
    if (item.m_param.empty())
        return nullptr;
    return vsk_eval_text(item.m_param);
} // vsk_get_play_param

bool vsk_phrase_from_play_items(std::shared_ptr<VskPhrase> phrase, const std::vector<VskPlayItem>& items)
{
    float length;
    int key = 0;
    for (auto& item : items) {
        char ch = item.m_subcommand[0];
        switch (ch) {
        case ' ': case '\t': // blank
            continue;
        case 'M':
            // TODO:
            assert(0);
            continue;
        case 'S':
            // TODO:
            assert(0);
            continue;
        case 'V':
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((0 <= i0) && (i0 <= 15)) {
                    phrase->m_setting.m_volume = i0;
                    continue;
                }
                return false;
            } else {
                phrase->m_setting.m_volume = 8;
            }
            continue;
        case 'L':
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((1 <= i0) && (i0 <= 64)) {
                    phrase->m_setting.m_length = (24.0f * 4.0f) / i0;
                    continue;
                }
                return false;
            } else {
                phrase->m_setting.m_length = (24.0f * 4.0f);
            }
            continue;
        case 'Q':
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((0 <= i0) && (i0 <= 8)) {
                    phrase->m_setting.m_quantity = i0;
                    continue;
                }
                return false;
            } else {
                phrase->m_setting.m_quantity = 8;
            }
            continue;
        case 'O':
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((1 <= i0) && (i0 <= 8)) {
                    phrase->m_setting.m_octave = i0 - 1;
                    continue;
                }
                return false;
            } else {
                phrase->m_setting.m_octave = 4 - 1;
            }
            continue;
        case '<':
            if (0 < phrase->m_setting.m_octave) {
                (phrase->m_setting.m_octave)--;
                continue;
            }
            return false;
        case '>':
            if (phrase->m_setting.m_octave < 8) {
                (phrase->m_setting.m_octave)++;
                continue;
            }
            return false;
        case 'N': case 'K':
            length = phrase->m_setting.m_length;
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((0 <= i0) && (i0 <= 96)) {
                    key = i0;
                    if (key >= 96) {
                        key = 0;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
            if ((item.m_plet_count > 1) && (item.m_plet_L != 0)) {
                auto L = item.m_plet_L;
                if ((1 <= L) && (L <= 64)) {
                    length = float(24 * 4 / L);
                } else {
                    return false;
                }
                length /= item.m_plet_count;
            }
            phrase->add_key(key, item.m_dot, length, item.m_sign);
            phrase->m_notes.back().m_and = item.m_and;
            continue;
        case 'T':
            if (auto ast = vsk_get_play_param(item)) {
                auto i0 = vsk_round(ast->value());
                if ((32 <= i0) && (i0 <= 255)) {
                    phrase->m_setting.m_tempo = i0;
                    continue;
                }
                return false;
            } else {
                phrase->m_setting.m_tempo = 120;
            }
            continue;
        case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'A': case 'B': case 'R': case 'P':
            if (ch == 'P') {
                ch = 'R';
            }
            length = phrase->m_setting.m_length;
            if (auto ast = vsk_get_play_param(item)) {
                auto L = ast->value();
                // NOTE: 24 is the length of a quarter note
                if ((1 <= L) && (L <= 64)) {
                    length = float(24 * 4 / L);
                } else {
                    return false;
                }
            }
            if ((item.m_plet_count > 1) && (item.m_plet_L != 0)) {
                auto L = item.m_plet_L;
                if ((1 <= L) && (L <= 64)) {
                    length = float(24 * 4 / L);
                } else {
                    return false;
                }
                length /= item.m_plet_count;
            }
            phrase->add_note(ch, item.m_dot, length, item.m_sign);
            phrase->m_notes.back().m_and = item.m_and;
            continue;
        case '@':
            if (item.m_subcommand == "@") {
                if (auto ast = vsk_get_play_param(item)) {
                    auto i0 = vsk_round(ast->value());
                    if ((0 <= i0) && (i0 <= 61)) {
                        phrase->m_setting.m_tone = i0;
                        continue;
                    }
                }
            } else if (item.m_subcommand == "@V") {
                if (auto ast = vsk_get_play_param(item)) {
                    auto i0 = vsk_round(ast->value());
                    if ((0 <= i0) && (i0 <= 127)) {
                        phrase->m_setting.m_volume =  i0 * (15.0f / 127.0f);
                        continue;
                    }
                }
            } else if (item.m_subcommand == "@W") {
                // TODO:
                assert(0);
                continue;
            }
            return false;
        case 'Y':
        case ',':
            // TODO:
            assert(0);
            continue;
        default:
            assert(0);
            break;
        }
    }
    return true;
} // vsk_phrase_from_play_items

//////////////////////////////////////////////////////////////////////////////

bool vsk_init_sound(void)
{
    if (!alutInit(NULL, NULL))
    {
        ALenum error = alutGetError();
        std::fprintf(stderr, "%s\n", alutGetErrorString(error));
        return false;
    }
    vsk_sound_player = std::make_shared<VskSoundPlayer>();
    return true;
}

void vsk_exit_sound(void)
{
    alutExit();
    vsk_sound_player = nullptr;
}

void vsk_sound_beep(int i)
{
    assert(vsk_sound_player);
    if (vsk_sound_player)
        vsk_sound_player->beep(i);
}

// SSG音源で音楽再生
bool vsk_sound_play_ssg(const std::vector<VskString>& strs)
{
    assert(strs.size() < VSK_MAX_CHANNEL);
    size_t iChannel = 0;

    // add phrases to block
    VskScoreBlock block;
    // for each channel strings
    for (auto& str : strs) {
        // get play items
        std::vector<VskPlayItem> items;
        if (!vsk_eval_play_items(items, str)) {
            return false;
        }

        // create phrase
        auto phrase = std::make_shared<VskPhrase>();
        phrase->m_setting = vsk_ssg_sound_settings[iChannel];
        phrase->m_setting.m_fm = false;
        if (!vsk_phrase_from_play_items(phrase, items)) {
            return false;
        }
        // apply settings
        vsk_ssg_sound_settings[iChannel] = phrase->m_setting;
        // add phrase
        block.push_back(phrase);
        // apply settings
        vsk_ssg_sound_settings[iChannel] = phrase->m_setting;
        // next channel
        ++iChannel;
    }

    // play now
    vsk_sound_player->play(block);

    return true;
}

// FM+SSG音源で音楽再生
bool vsk_sound_play_fm_and_ssg(const std::vector<VskString>& strs)
{
    assert(strs.size() < VSK_MAX_CHANNEL);
    size_t iChannel = 0;

    // add phrases to block
    VskScoreBlock block;
    // for each channel strings
    for (auto& str : strs) {
        // get play items
        std::vector<VskPlayItem> items;
        if (!vsk_eval_play_items(items, str)) {
            return false;
        }
        // create phrase
        auto phrase = std::make_shared<VskPhrase>();
        if (iChannel < 3) {
            phrase->m_setting = vsk_fm_sound_settings[iChannel];
            phrase->m_setting.m_fm = true;
        } else {
            phrase->m_setting = vsk_ssg_sound_settings[iChannel - 3];
            phrase->m_setting.m_fm = false;
        }
        if (!vsk_phrase_from_play_items(phrase, items)) {
            return false;
        }
        // apply settings
        if (iChannel < 3) {
            vsk_fm_sound_settings[iChannel] = phrase->m_setting;
        } else {
            vsk_ssg_sound_settings[iChannel] = phrase->m_setting;
        }
        // add phrase
        block.push_back(phrase);
        // next channel
        ++iChannel;
    }

    // play now
    vsk_sound_player->play(block);

    return true;
}

// FM音源で音楽再生
bool vsk_sound_play_fm(const std::vector<VskString>& strs)
{
    assert(strs.size() < VSK_MAX_CHANNEL);
    size_t iChannel = 0;

    // add phrases to block
    VskScoreBlock block;
    // for each channel strings
    for (auto& str : strs) {
        // get play items
        std::vector<VskPlayItem> items;
        if (!vsk_eval_play_items(items, str)) {
            return false;
        }
        // create phrase
        auto phrase = std::make_shared<VskPhrase>();
        phrase->m_setting = vsk_fm_sound_settings[iChannel];
        phrase->m_setting.m_fm = true;
        if (!vsk_phrase_from_play_items(phrase, items)) {
            return false;
        }
        // apply settings
        vsk_fm_sound_settings[iChannel] = phrase->m_setting;
        // add phrase
        block.push_back(phrase);
        // next channel
        ++iChannel;
    }

    // play now
    vsk_sound_player->play(block);

    return true;
}
