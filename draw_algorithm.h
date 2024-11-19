#pragma once

#include <cassert>

// ANK文字のピクセルを取得するクラス
template <int t_width = 128, int t_height = 256>
struct VskAnkGetter {
    const VskByte *m_bits = nullptr;
    VskAnkGetter() = default;
    constexpr VskAnkGetter(int width, int height, const VskByte *bits) : m_bits(bits) {
        assert(t_width == width);
        assert(t_height == height);
    }
    constexpr void set(int width, int height, const VskByte *bits) {
        m_bits = bits;
        assert(t_width == width);
        assert(t_height == height);
    }
    bool operator()(int x, int y) const {
        if (0 <= x && x < t_width && 0 <= y && y < t_height) {
            int offset = y * (t_width / CHAR_BIT) + x / CHAR_BIT;
            auto& byte = m_bits[offset];
            return ((byte >> (x % CHAR_BIT)) & 1);
        }
        return false;
    }
};

// 8801っぽいANKのピクセルを取得するクラス
struct Vsk8801AnkGetter : VskAnkGetter<> {
    Vsk8801AnkGetter() {
#include "img/pc88_chars.xbm"
        set(pc88_chars_width, pc88_chars_height, pc88_chars_bits);
    }
};

// 9801っぽいANKのピクセルを取得するクラス
struct Vsk9801AnkGetter : VskAnkGetter<> {
    Vsk9801AnkGetter() {
#include "img/pc98_chars.xbm"
        set(pc98_chars_width, pc98_chars_height, pc98_chars_bits);
    }
};

// セミグラ文字のピクセルを取得するクラス
struct VskSemiGraAnkGetter : VskAnkGetter<> {
    VskSemiGraAnkGetter() {
#include "img/semigra.xbm"
        set(semigra_width, semigra_height, semigra_bits);
    }
};

// PUT@ ANK (PANK) 文字のピクセルを取得するクラス
struct VskPankGetter : VskAnkGetter<> {
    VskPankGetter() {
#include "img/pc98_pank.xbm"
        set(pc98_pank_width, pc98_pank_height, pc98_pank_bits);
    }
};

// 全角文字のピクセルを取得するクラス
struct VskKanjiGetter {
    const VskByte *m_bits = nullptr;
    VskKanjiGetter() {
#include "img/kanji_chars.xbm"
        m_bits = kanji_chars_bits;
    }
    enum {
        t_width = kanji_chars_width,
        t_height = kanji_chars_height,
    };
    bool operator()(int x, int y) const {
        if (0 <= x && x < t_width && 0 <= y && y < t_height) {
            int offset = y * (t_width / CHAR_BIT) + x / CHAR_BIT;
            auto& byte = m_bits[offset];
            return ((byte >> (x % CHAR_BIT)) & 1);
        }
        return false;
    }
};

// ピクセルを置かないクラス
struct VskNullPutter
{
    void operator()(int x, int y) { }
};

// 白黒イメージのピクセルを取得するクラス
struct VskMonoGetter
{
    int m_width = 0;
    int m_height = 0;
    const VskByte *m_bits = nullptr;
    constexpr VskMonoGetter(int width, int height, const VskByte *bits)
        : m_width(width)
        , m_height(height)
        , m_bits(bits)
    {
    }
    bool operator()(int x, int y) const {
        if (0 <= x && x < m_width && 0 <= y && y < m_height) {
            int offset = y * (m_width / CHAR_BIT) + (x / CHAR_BIT);
            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            auto& byte = m_bits[offset];
            if (byte & (1 << ibit))
                return true;
        }
        return false;
    }
};

// 境界を取得する
template <typename T_GETTER>
struct VskBorderGetter
{
    int m_color = 0;
    T_GETTER *m_color_getter = nullptr;
    VskBorderGetter(int color, T_GETTER *color_getter)
        : m_color(color)
        , m_color_getter(color_getter)
    {
    }
    bool operator()(int x, int y) const
    {
        int color = (*m_color_getter)(x, y);
        if (color == -1)
            return true;
        return color == m_color;
    }
};

// 点線を描く
template <typename T_PUTTER>
struct VskLinePutter
{
    T_PUTTER *m_putter = nullptr;
    int m_ibit = 0;
    VskWord m_line_style = 0xFFFF;
    VskWord m_bits = 0;

    VskLinePutter(T_PUTTER *putter, VskWord line_style = 0xFFFF)
        : m_putter(putter)
        , m_line_style(line_style)
        , m_bits(sizeof(VskWord) * CHAR_BIT)
    {
    }

    void operator()(int x, int y) {
        if (m_line_style & (1 << (m_bits - m_ibit - 1)))
            (*m_putter)(x, y);
        m_ibit++;
        m_ibit %= m_bits;
    }
};

// 線分を描画する
template <typename T_PUTTER>
inline void vsk_draw_line(T_PUTTER& putter, int x0, int y0, int x1, int y1)
{
    // Bresenham's line algorithm
    const int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
    const int sx = ((x0 < x1) ? 1 : -1), sy = ((y0 < y1) ? 1 : -1);
    int err = dx - dy;
    for (;;) {
        putter(x0, y0);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// vsk_compute_outcodeとvsk_draw_lineにおけるクリッピングで使う定数
enum VSK_OUTCODE : int {
    VSK_OC_INSIDE = 0,  // クリッピングの内部
    VSK_OC_LEFT   = 1,  // クリッピングの左側
    VSK_OC_RIGHT  = 2,  // クリッピングの右側
    VSK_OC_TOP    = 4,  // クリッピングの下側
    VSK_OC_BOTTOM = 8   // クリッピングの上側
};

// 各点のコードを生成する関数
inline int vsk_compute_outcode(int x, int y, const VskRectI *clipping)
{
    int code = VSK_OC_INSIDE; // 最初はクリッピング内にあると仮定

    if (x < clipping->m_x0)       // 左側にある
        code |= VSK_OC_LEFT;
    else if (x > clipping->m_x1)  // 右側にある
        code |= VSK_OC_RIGHT;

    if (y < clipping->m_y0)       // 上側にある
        code |= VSK_OC_TOP;
    else if (y > clipping->m_y1)  // 下側にある
        code |= VSK_OC_BOTTOM;

    return code;
}

// クリッピングされた線分の描画
template <typename T_PUTTER>
inline void
vsk_draw_line(T_PUTTER& putter, int x0, int y0, int x1, int y1, const VskRectI *clipping)
{
    if (!clipping) {
        vsk_draw_line(putter, x0, y0, x1, y1);
        return;
    }

    // Cohen-Sutherland clipping algorithm
    int outcode0 = vsk_compute_outcode(x0, y0, clipping);
    int outcode1 = vsk_compute_outcode(x1, y1, clipping);

    for (;;) {
        if ((outcode0 | outcode1) == 0) {
            // 両方の点がクリッピング内にある場合
            vsk_draw_line(putter, x0, y0, x1, y1); // クリッピングされた線分を描画
            return; // 終了
        } else if (outcode0 & outcode1) {
            // 両方の点が同じ外側にある場合（完全に外れている）
            break;
        } else {
            // クリッピングが必要
            int outcode_out = outcode0 ? outcode0 : outcode1;
            int x, y;

            if (outcode_out & VSK_OC_RIGHT) {
                // 線がクリッピングの右を越える
                y = y0 + (y1 - y0) * (clipping->m_x1 - x0) / (x1 - x0);
                x = clipping->m_x1;
            } else if (outcode_out & VSK_OC_BOTTOM) {
                // 線がクリッピングの下を越える
                x = x0 + (x1 - x0) * (clipping->m_y1 - y0) / (y1 - y0);
                y = clipping->m_y1;
            } else if (outcode_out & VSK_OC_TOP) {
                // 線がクリッピングの上を越える
                x = x0 + (x1 - x0) * (clipping->m_y0 - y0) / (y1 - y0);
                y = clipping->m_y0;
            } else if (outcode_out & VSK_OC_LEFT) {
                // 線がクリッピングの左を越える
                y = y0 + (y1 - y0) * (clipping->m_x0 - x0) / (x1 - x0);
                x = clipping->m_x0;
            }

            // クリッピングされた点を更新
            if (outcode_out == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = vsk_compute_outcode(x0, y0, clipping);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = vsk_compute_outcode(x1, y1, clipping);
            }
        }
    }
}

// 長方形を描画
template <typename T_PUTTER>
inline void vsk_draw_box(T_PUTTER& putter, int x0, int y0, int x1, int y1)
{
    vsk_draw_line<T_PUTTER>(putter, x0, y0, x1, y0);
    vsk_draw_line<T_PUTTER>(putter, x1, y0, x1, y1);
    vsk_draw_line<T_PUTTER>(putter, x1, y1, x0, y1);
    vsk_draw_line<T_PUTTER>(putter, x0, y1, x0, y0);
}

// クリッピングされた長方形を描画
template <typename T_PUTTER>
inline void vsk_draw_box(T_PUTTER& putter, int x0, int y0, int x1, int y1, const VskRectI *clipping)
{
    vsk_draw_line<T_PUTTER>(putter, x0, y0, x1, y0, clipping);
    vsk_draw_line<T_PUTTER>(putter, x1, y0, x1, y1, clipping);
    vsk_draw_line<T_PUTTER>(putter, x1, y1, x0, y1, clipping);
    vsk_draw_line<T_PUTTER>(putter, x0, y1, x0, y0, clipping);
}

// 長方形を塗りつぶす
template <typename T_PUTTER>
inline void vsk_fill_box(T_PUTTER& putter, int x0, int y0, int x1, int y1, const VskRectI *clipping = nullptr)
{
    if (x0 > x1) std::swap(x0, x1);
    if (y0 > y1) std::swap(y0, y1);
    if (clipping) {
        x0 = std::max(x0, clipping->m_x0);
        x1 = std::min(x1, clipping->m_x1);
        y0 = std::max(y0, clipping->m_y0);
        y1 = std::min(y1, clipping->m_y1);
    }
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            putter(x, y);
        }
    }
}

// 円を描く
template <typename T_PUTTER>
inline void vsk_draw_circle(T_PUTTER& putter, int x0, int y0, int radius, const VskRectI *clipping = nullptr)
{
    // Midpoint Circle Algorithm (also known as Bresenham's Circle Algorithm)
    int x = radius, y = 0, err = 0;
    while (x >= y) {
        putter(x0 + x, y0 + y);
        putter(x0 + y, y0 + x);
        putter(x0 - y, y0 + x);
        putter(x0 - x, y0 + y);
        putter(x0 - x, y0 - y);
        putter(x0 - y, y0 - x);
        putter(x0 + y, y0 - x);
        putter(x0 + x, y0 - y);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

// 円の内部を塗りつぶす。
template <typename T_PUTTER>
inline void vsk_fill_circle(T_PUTTER& putter, int x0, int y0, int radius, const VskRectI *clipping = nullptr)
{
    // Modified Midpoint Circle Algorithm with horizontal line filling
    int x = radius, y = 0;
    int xChange = 1 - (radius << 1), yChange = 0;
    int radiusError = 0;

    while (x >= y) {
        for (int i = x0 - x; i <= x0 + x; i++) {
            putter(i, y0 + y);
            putter(i, y0 - y);
        }
        for (int i = x0 - y; i <= x0 + y; i++) {
            putter(i, y0 + x);
            putter(i, y0 - x);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0) {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

// 楕円を描画する。
template <typename T_PUTTER>
inline void vsk_draw_ellipse(T_PUTTER& putter, int x0, int y0, int x1, int y1, const VskRectI *clipping = nullptr)
{
    // Midpoint Ellipse Algorithm
    int a = std::abs(x1 - x0), b = std::abs(y1 - y0), b1 = (b & 1); // 半径
    int dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; // エラー増分
    int err = dx + dy + b1 * a * a, e2; // エラーステップ

    if (x0 > x1) { x0 = x1; x1 += a; } // 左端から右端へ
    if (y0 > y1) y0 = y1; // 下から上へ
    y0 += (b + 1) / 2;
    y1 = y0 - b1;
    a *= 8 * a;
    b1 = 8 * b * b;

    do {
        putter(x1, y0); // 第1象限
        putter(x0, y0); // 第2象限
        putter(x0, y1); // 第3象限
        putter(x1, y1); // 第4象限

        e2 = 2 * err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  // y step
        if (e2 >= dx || 2 * err > dy) { x0++; x1--; err += dx += b1; } // x step
    } while (x0 <= x1);

    // 残りの点を処理
    while (y0 - y1 <= b) {
        putter(x0 - 1, y0); // 第1象限に点を打つ
        putter(x1 + 1, y0++); // 第4象限に点を打つ
        putter(x0 - 1, y1); // 第2象限に点を打つ
        putter(x1 + 1, y1--); // 第3象限に点を打つ
    }
}

// 楕円の内部を塗りつぶす。
template <typename T_PUTTER>
inline void vsk_fill_ellipse(T_PUTTER& putter, int x0, int y0, int x1, int y1, const VskRectI *clipping = nullptr)
{
    // Modified Midpoint Ellipse Algorithm with horizontal line filling
    int a = std::abs(x1 - x0), b = std::abs(y1 - y0), b1 = (b & 1); // 半径
    int dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; // エラー増分
    int err = dx + dy + b1 * a * a, e2; // エラーステップ

    if (x0 > x1) { x0 = x1; x1 += a; } // 左端から右端へ
    if (y0 > y1) y0 = y1; // 下から上へ
    y0 += (b + 1) / 2;
    y1 = y0 - b1;
    a *= 8 * a;
    b1 = 8 * b * b;

    do {
        int x_left = x0, x_right = x1;

        // 現在の行を塗りつぶす
        for (int x = x_left; x <= x_right; ++x) {
            putter(x, y0);
            putter(x, y1);
        }

        e2 = 2 * err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  // y step
        if (e2 >= dx || 2 * err > dy) { x0++; x1--; err += dx += b1; } // x step
    } while (x0 <= x1);

    // 残りの中央部分を塗りつぶす
    while (y0 - y1 <= b) {
        for (int x = x0 - 1; x <= x1 + 1; ++x) {
            putter(x, y0);
            putter(x, y1);
        }
        y0++;
        y1--;
    }
}

// 円の弧または楕円の弧を描画する。角度が負なら半径も描画する
template <typename T_PUTTER>
void vsk_draw_arc(T_PUTTER& putter, int x0, int y0, int x1, int y1, double start_angle, double end_angle, const VskRectI *clipping = nullptr)
{
    // 角度が負なら半径を描画するフラグをtrueにする
    const bool line0 = (start_angle < 0), line1 = (end_angle < 0);
    // 中心を計算する
    const int center_x = (x0 + x1) / 2, center_y = (y0 + y1) / 2;
    // 直径を計算する
    int a0 = std::abs(x1 - x0), b0 = std::abs(y1 - y0);
    // ゼロはまずいので補正
    if (a0 <= 0) a0 = 1;
    // アスペクト比
    const double aspect = double(b0) / a0;

    // 角度は絶対値を使う
    start_angle = std::abs(start_angle);
    end_angle = std::abs(end_angle);
    // 角度を正規化
    start_angle = std::fmod(start_angle, 2 * M_PI);
    end_angle = std::fmod(end_angle, 2 * M_PI);
    if (start_angle < 0) start_angle += 2 * M_PI;
    if (end_angle < 0) end_angle += 2 * M_PI;

    int a = a0, b = b0, b1 = (b & 1);
    int dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; // エラー増分
    int err = dx + dy + b1 * a * a, e2; // エラーステップ

    if (x0 > x1) { x0 = x1; x1 += a; } // 左端から右端へ
    if (y0 > y1) y0 = y1; // 下から上へ
    y0 += (b + 1) / 2;
    y1 = y0 - b1;
    a *= 8 * a;
    b1 = 8 * b * b;

    // 弧がなす角度が範囲内かどうか調べる関数
    auto arc_in_range = [&](int x, int y) {
        double dx = x - center_x, dy = (y - center_y) / aspect;
        auto angle = std::atan2(-dy, dx); // 数学とはY軸の向きが違う
        if (angle < 0)
            angle = 2 * M_PI;
        if (start_angle <= end_angle)
            return start_angle <= angle && angle <= end_angle;
        return angle <= end_angle || start_angle <= angle;
    };
    // 弧の上ならピクセルをセットする関数
    auto putter2 = [&](int x, int y) {
        if (arc_in_range(x, y)) {
            putter(x, y);
        }
    };

    do {
        putter2(x1, y0); // 第1象限
        putter2(x0, y0); // 第2象限
        putter2(x0, y1); // 第3象限
        putter2(x1, y1); // 第4象限

        e2 = 2 * err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  // y step
        if (e2 >= dx || 2 * err > dy) { x0++; x1--; err += dx += b1; } // x step
    } while (x0 <= x1);

    while (y0 - y1 <= b) {
        putter2(x0 - 1, y0); // 第1象限に点を打つ
        putter2(x1 + 1, y0++); // 第4象限に点を打つ
        putter2(x0 - 1, y1); // 第2象限に点を打つ
        putter2(x1 + 1, y1--); // 第3象限に点を打つ
    }

    // 必要なら半径を描画する
    if (line0) {
        double x = center_x + a0 * std::cos(start_angle) / 2;
        double y = center_y - b0 * std::sin(start_angle) / 2; // 数学とはY軸の向きが違う
        vsk_draw_line(putter, center_x, center_y, (int)std::round(x), (int)std::round(y), clipping);
    }
    if (line1) {
        double x = center_x + a0 * std::cos(end_angle) / 2;
        double y = center_y - b0 * std::sin(end_angle) / 2; // 数学とはY軸の向きが違う
        vsk_draw_line(putter, center_x, center_y, (int)std::round(x), (int)std::round(y), clipping);
    }
}

// 円の弧または楕円の弧を塗りつぶす
template <typename T_PUTTER>
inline void vsk_fill_arc(T_PUTTER& putter, int x0, int y0, int x1, int y1, double start_angle, double end_angle, const VskRectI *clipping = nullptr)
{
    // 中心を計算する
    const int center_x = (x0 + x1) / 2, center_y = (y0 + y1) / 2;
    // 直径を計算する
    int a0 = std::abs(x1 - x0), b0 = std::abs(y1 - y0);
    // ゼロはまずいので補正
    if (a0 <= 0) a0 = 1;
    // アスペクト比
    const double aspect = double(b0) / a0;
    // 角度は絶対値を使う
    start_angle = std::abs(start_angle);
    end_angle = std::abs(end_angle);
    // 角度を正規化
    start_angle = std::fmod(start_angle, 2 * M_PI);
    end_angle = std::fmod(end_angle, 2 * M_PI);
    if (start_angle < 0) start_angle += 2 * M_PI;
    if (end_angle < 0) end_angle += 2 * M_PI;

    // 弧の内部かどうか調べる関数
    auto arc_in_range = [&](int x, int y) {
        double dx = x - center_x, dy = (y - center_y) / aspect;
        auto angle = std::atan2(-dy, dx); // 数学とはY軸の向きが違う
        if (angle < 0)
            angle = 2 * M_PI;
        if (start_angle <= end_angle) {
            if (!(start_angle <= angle && angle <= end_angle))
                return false;
            return (dx * dx) + (dy * dy) <= a0 * a0 / 4;
        }
        if (!(angle <= end_angle || start_angle <= angle))
            return false;
        return (dx * dx) + (dy * dy) <= a0 * a0 / 4;
    };
    // 弧の内部ならピクセルをセットする関数
    auto putter2 = [&](int x, int y) {
        if (arc_in_range(x, y)) {
            putter(x, y);
        }
    };

    if (x0 > x1) std::swap(x0, x1);
    if (y0 > y1) std::swap(y0, y1);

    if (clipping) {
        x0 = std::max(x0, clipping->m_x0);
        x1 = std::min(x1, clipping->m_x1);
        y0 = std::max(y0, clipping->m_y0);
        y1 = std::min(y1, clipping->m_y1);
    }

    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            putter2(x, y);
        }
    }
}

// ANK文字を描画する
template <typename T_PUTTER, typename T_ERASER, typename T_GETTER>
inline void vk_draw_ank(T_PUTTER& putter, T_ERASER& eraser, int x0, int y0, VskByte ch, const T_GETTER& getter, bool underline, bool upperline = false)
{
    auto xSrc = (ch & 0xF) * 8, ySrc = (ch >> 4) * 16;
    for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
            if (getter(xSrc + dx, ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
}

// JISの全角文字を描画する
template <typename T_PUTTER, typename T_ERASER, typename T_GETTER>
inline void vk_draw_jis(T_PUTTER& putter, T_ERASER& eraser, int x0, int y0, int x1, int y1, VskWord jis, const T_GETTER& getter, bool underline, bool upperline = false)
{
    auto xSrc = (vsk_low_byte(jis) - 0x21) * 16, ySrc = (vsk_high_byte(jis) - 0x21) * 16;
    for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
            if (getter(xSrc + dx, ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
    for (int dy = 0, y = y1; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 8, x = x1; dx < 16; ++x, ++dx) {
            if (getter(xSrc + dx, ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
}

// 幅の広いANK文字を描画する
template <typename T_PUTTER, typename T_ERASER, typename T_GETTER>
inline void vk_draw_wide_ank(T_PUTTER& putter, T_ERASER& eraser, int x0, int y0, VskByte ch, const T_GETTER& getter, bool underline, bool upperline = false)
{
    auto xSrc = (ch & 0xF) * 8, ySrc = (ch >> 4) * 16;
    for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
            if (getter(xSrc + (dx >> 1), ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
}

// 幅の広いJISの全角文字を描画する
template <typename T_PUTTER, typename T_ERASER, typename T_GETTER>
inline void vk_draw_wide_jis(T_PUTTER& putter, T_ERASER& eraser, int x0, int y0, int x1, int y1, VskWord jis, const T_GETTER& getter, bool underline, bool upperline = false)
{
    auto xSrc = (vsk_low_byte(jis) - 0x21) * 16, ySrc = (vsk_high_byte(jis) - 0x21) * 16;
    for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
            if (getter(xSrc + (dx >> 1), ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
    for (int dy = 0, y = y1; dy < 16; ++y, ++dy) {
        bool flag = (upperline && dy == 0) || (underline && dy == 15);
        for (int dx = 16, x = x1; dx < 32; ++x, ++dx) {
            if (getter(xSrc + (dx >> 1), ySrc + dy) | flag)
                putter(x, y);
            else
                eraser(x, y);
        }
    }
}

// 境界内を塗りつぶす
template <typename T_PUTTER, typename T_GETTER>
inline void vsk_flood_fill(T_PUTTER& putter, T_GETTER& border_getter, int x, int y, const VskRectI *clipping = nullptr)
{
    if (border_getter(x, y))
        return;

    std::vector<VskPointI> points;
    VskPointI pt = { x, y };
    points.push_back(pt);

    struct VskPointILess {
        inline bool operator()(const VskPointI& p0, const VskPointI& p1) const {
            if (p0.m_x < p1.m_x)
                return true;
            return p0.m_x == p1.m_x && p0.m_y < p1.m_y;
        }
    };

    std::set<VskPointI, VskPointILess> point_set;
    point_set.insert(pt);

    while (!points.empty()) {
        pt = points.back();
        points.pop_back();

        if (border_getter(pt.m_x, pt.m_y))
            continue;

        putter(pt.m_x, pt.m_y);

        auto add_point = [&](int new_x, int new_y) {
            if (!border_getter(new_x, new_y) && point_set.insert({new_x, new_y}).second) {
                points.push_back({new_x, new_y});
            }
        };

        if (!clipping || (pt.m_x > clipping->m_x0)) add_point(pt.m_x - 1, pt.m_y); // left
        if (!clipping || (pt.m_y > clipping->m_y0)) add_point(pt.m_x, pt.m_y - 1); // up
        if (!clipping || (pt.m_x < clipping->m_x1)) add_point(pt.m_x + 1, pt.m_y); // right
        if (!clipping || (pt.m_y < clipping->m_y1)) add_point(pt.m_x, pt.m_y + 1); // down
    }
}

// スクロールする
template <typename T_PUTTER, typename T_GETTER>
void vsk_draw_scroll(T_PUTTER& putter, T_GETTER& getter, int dx, int dy, int fill_color, const VskRectI *clipping)
{
    // NOTE: 難しいときは次元を下げて考えてみよう。
    if (dy > 0) {
        if (dx > 0) {
            for (int x = clipping->m_x1; x >= clipping->m_x0 + dx; --x) {
                for (int y = clipping->m_y1; y >= clipping->m_y0 + dy; --y) {
                    int palette = getter(x - dx, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x0 + dx, clipping->m_y1, clipping);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x1, clipping->m_y0 + dy, clipping);
        } else if (dx < 0) {
            for (int x = clipping->m_x0; x <= clipping->m_x1 - dx; ++x) {
                for (int y = clipping->m_y0; y <= clipping->m_y1 - dy; ++y) {
                    int palette = getter(x - dx, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x1 + dx, clipping->m_y0, clipping->m_x1, clipping->m_y1, clipping);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x1, clipping->m_y0 + dy, clipping);
        } else {
            assert(dx == 0);
            for (int x = clipping->m_x0; x <= clipping->m_x1; ++x) {
                for (int y = clipping->m_y1; y >= clipping->m_y0 + dy; --y) {
                    int palette = getter(x, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x1, clipping->m_y0 + dy, clipping);
        }
    } else if (dy < 0) {
        if (dx > 0) {
            for (int x = clipping->m_x1; x >= clipping->m_x0 + dx; --x) {
                for (int y = clipping->m_y0; y <= clipping->m_y1 - dy; ++y) {
                    int palette = getter(x - dx, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x0 + dx, clipping->m_y1, clipping);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y1 + dy, clipping->m_x1, clipping->m_y1, clipping);
        } else if (dx < 0) {
            for (int x = clipping->m_x0; x <= clipping->m_x1 - dx; ++x) {
                for (int y = clipping->m_y0; x <= clipping->m_y1 - dy; ++y) {
                    int palette = getter(x - dx, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x1 + dx, clipping->m_y0, clipping->m_x1, clipping->m_y1, clipping);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y1 + dy, clipping->m_x1, clipping->m_y1, clipping);
        } else {
            assert(dx == 0);
            for (int x = clipping->m_x0; x <= clipping->m_x1; ++x) {
                for (int y = clipping->m_y0; y <= clipping->m_y1 - dy; ++y) {
                    int palette = getter(x, y - dy);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y1 + dy, clipping->m_x1, clipping->m_y1, clipping);
        }
    } else {
        assert(dy == 0);
        if (dx > 0) {
            for (int x = clipping->m_x1; x >= clipping->m_x0 + dx; --x) {
                for (int y = clipping->m_y0; y <= clipping->m_y1; ++y) {
                    int palette = getter(x - dx, y);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x0, clipping->m_y0, clipping->m_x0 + dx, clipping->m_y1, clipping);
        } else if (dx < 0) {
            for (int x = clipping->m_x0; x <= clipping->m_x1 - dx; ++x) {
                for (int y = clipping->m_y0; y <= clipping->m_y1; ++y) {
                    int palette = getter(x - dx, y);
                    putter.set_color(palette);
                    putter(x, y);
                }
            }
            putter.set_color(fill_color);
            vsk_fill_box(putter, clipping->m_x1 + dx, clipping->m_y0, clipping->m_x1, clipping->m_y1, clipping);
        } else {
            assert(dx == 0 && dy == 0);
        }
    }
}

// ANK 文字を描画する
template <typename T_KANJI_GETTER, typename T_PUTTER, typename T_GETTER>
void vsk_draw_ank(T_KANJI_GETTER& kanji_getter, T_PUTTER& putter, T_GETTER& getter, VskWord code, int x0, int y0, int fore_color, int back_color, const VskString& op)
{
    assert(code <= 0xFF);
    auto xSrc = (code & 0xF) * 8, ySrc = (code >> 4) * 16;
    if (op == "XOR" || op.empty()) {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette ^= fore_color;
                else
                    palette ^= back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "OR") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette |= fore_color;
                else
                    palette |= back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "AND") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
                int palette = getter(x, y);
                if (!kanji_getter(xSrc + dx, ySrc + dy))
                    palette &= 0;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PSET") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette = fore_color;
                else
                    palette = back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PRESET") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 8; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette = back_color;
                else
                    palette = fore_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    }
}

// PANK (PUT@ ANK) 文字を描画する
template <typename T_PUTTER, typename T_GETTER>
void vsk_draw_pank(T_PUTTER& putter, T_GETTER& getter, VskWord code, int x0, int y0, int fore_color, int back_color, const VskString& op, bool is_9801)
{
    assert(code <= 0xFF);
    if (is_9801) {
        VskPankGetter kanji_getter;
        vsk_draw_ank(kanji_getter, putter, getter, code, x0, y0, fore_color, back_color, op);
    } else {
        Vsk9801AnkGetter kanji_getter;
        vsk_draw_ank(kanji_getter, putter, getter, code, x0, y0, fore_color, back_color, op);
    }
}

// JISの文字を描画する
template <typename T_PUTTER, typename T_GETTER>
void vsk_draw_kanji(T_PUTTER& putter, T_GETTER& getter, VskWord jis, int x0, int y0, int fore_color, int back_color, const VskString& op, bool is_9801)
{
    if (jis <= 0xFF) {
        vsk_draw_pank(putter, getter, jis, x0, y0, fore_color, back_color, op, is_9801);
        return;
    }
    VskKanjiGetter kanji_getter;
    auto xSrc = (vsk_low_byte(jis) - 0x21) * 16, ySrc = (vsk_high_byte(jis) - 0x21) * 16;
    if (op == "XOR" || op.empty()) {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette ^= fore_color;
                else
                    palette ^= back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "OR") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette |= fore_color;
                else
                    palette |= back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "AND") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
                int palette = getter(x, y);
                if (!kanji_getter(xSrc + dx, ySrc + dy))
                    palette &= 0;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PSET") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette = fore_color;
                else
                    palette = back_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PRESET") {
        for (int dy = 0, y = y0; dy < 16; ++y, ++dy) {
            for (int dx = 0, x = x0; dx < 16; ++x, ++dx) {
                int palette = getter(x, y);
                if (kanji_getter(xSrc + dx, ySrc + dy))
                    palette = back_color;
                else
                    palette = fore_color;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    }
}

struct VskImageGetter
{
    uint8_t *m_ptr;
    int m_pitch;
    int m_plane_size;
    size_t m_M;
    VskImageGetter(uint8_t *ptr, int pitch, int plane_size, size_t M)
        : m_ptr(ptr)
        , m_pitch(pitch)
        , m_plane_size(plane_size)
        , m_M(M)
    {
    }
    void operator()(int x, int y, int palette)
    {
        {
            if (palette & (1 << 0))
                m_ptr[y * m_pitch + x / 8 + 0 * m_plane_size] |= 1 << (7 - (x % 8));
        }
        if (m_M >= 3)
        {
            if (palette & (1 << 1))
                m_ptr[y * m_pitch + x / 8 + 1 * m_plane_size] |= 1 << (7 - (x % 8));
            if (palette & (1 << 2))
                m_ptr[y * m_pitch + x / 8 + 2 * m_plane_size] |= 1 << (7 - (x % 8));
        }
        if (m_M == 4)
        {
            if (palette & (1 << 3))
                m_ptr[y * m_pitch + x / 8 + 3 * m_plane_size] |= 1 << (7 - (x % 8));
        }
    }
};

template <typename T_GETTER>
bool vsk_get_image(T_GETTER& getter, int x0, int y0, int cx, int cy, uint8_t *ptr, size_t size, size_t M)
{
    if (size < 4)
        return false;

    ((uint16_t*)ptr)[0] = uint16_t(cx);
    ((uint16_t*)ptr)[1] = uint16_t(cy);
    ptr += 4;
    size -= 4;
    std::memset(ptr, 0, size);

    auto pitch = (cx + 7) / 8;
    size_t plane_size = pitch * cy;
    if (M * plane_size > size)
        return false;

    VskImageGetter getter2(ptr, pitch, plane_size, M);

    for (int y = y0; y < y0 + cy; ++y)
    {
        for (int x = x0; x < x0 + cx; ++x)
        {
            int palette = getter(x, y);
            if (palette == -1)
                continue;
            getter2(x - x0, y - y0, palette);
        }
    }

    return true;
}

struct VskImagePutter
{
    const uint8_t *m_ptr;
    int m_pitch;
    int m_plane_size;
    size_t m_M;
    VskImagePutter(const uint8_t *ptr, int pitch, int plane_size, size_t M)
        : m_ptr(ptr)
        , m_pitch(pitch)
        , m_plane_size(plane_size)
        , m_M(M)
    {
    }
    int operator()(int x, int y) const
    {
        int palette = 0;
        int ibit = (7 - (x % 8));
        if (m_ptr[y * m_pitch + x / 8 + 0 * m_plane_size] & (1 << ibit))
            palette |= 1 << 0;
        if (m_M >= 3)
        {
            if (m_ptr[y * m_pitch + x / 8 + 1 * m_plane_size] & (1 << ibit))
                palette |= 1 << 1;
            if (m_ptr[y * m_pitch + x / 8 + 2 * m_plane_size] & (1 << ibit))
                palette |= 1 << 2;
        }
        if (m_M == 4)
        {
            if (m_ptr[y * m_pitch + x / 8 + 3 * m_plane_size] & (1 << ibit))
                palette |= 1 << 3;
        }
        return palette;
    }
};

template <typename T_PUTTER, typename T_GETTER>
bool vsk_put_image(T_PUTTER& putter, T_GETTER& getter, int x0, int y0, const uint8_t *ptr, size_t size, size_t M, const VskString& op)
{
    if (size < 4)
        return false;

    const uint16_t cx = ((uint16_t*)ptr)[0];
    const uint16_t cy = ((uint16_t*)ptr)[1];
    ptr += 4;
    size -= 4;

    auto pitch = (cx + 7) / 8;
    size_t plane_size = pitch * cy;
    if (M * plane_size > size)
        return false;

    VskImagePutter putter2(ptr, pitch, plane_size, M);

    if (op == "XOR" || op.empty()) {
        for (int y = y0; y < y0 + cy; ++y) {
            for (int x = x0; x < x0 + cx; ++x) {
                int palette = getter(x, y);
                palette ^= putter2(x - x0, y - y0);
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "OR") {
        for (int y = y0; y < y0 + cy; ++y) {
            for (int x = x0; x < x0 + cx; ++x) {
                int palette = getter(x, y);
                palette |= putter2(x - x0, y - y0);
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "AND") {
        for (int y = y0; y < y0 + cy; ++y) {
            for (int x = x0; x < x0 + cx; ++x) {
                int palette = getter(x, y);
                palette &= putter2(x - x0, y - y0);
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PSET") {
        for (int y = y0; y < y0 + cy; ++y) {
            for (int x = x0; x < x0 + cx; ++x) {
                int palette = getter(x, y);
                palette = putter2(x - x0, y - y0);
                putter.set_color(palette);
                putter(x, y);
            }
        }
    } else if (op == "PRESET") {
        for (int y = y0; y < y0 + cy; ++y) {
            for (int x = x0; x < x0 + cx; ++x) {
                int palette = getter(x, y);
                palette = putter2(x - x0, y - y0) ^ 0xF;
                putter.set_color(palette);
                putter(x, y);
            }
        }
    }

    return true;
}
