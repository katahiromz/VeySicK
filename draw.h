#pragma once

#include "types.h"

//////////////////////////////////////////////////////////////////////////////
// VskDrawItem --- DRAW文による描画項目

struct VskDrawItem
{
    bool                    m_B;
    bool                    m_N;
    char                    m_subcommand;
    std::vector<VskString>  m_params;

    VskDrawItem() { reset(); }

    void reset() {
        m_B = m_N = false;
        m_subcommand = 0;
        m_params.clear();
    }
};

// 文字列をパースして描画項目にする
bool vsk_get_draw_items_from_string(std::vector<VskDrawItem>& items, const VskString& expr);

//////////////////////////////////////////////////////////////////////////////
// VskDrawItem --- DRAW文用の描画エンジン

struct VskDrawEngine
{
    std::vector<VskDrawItem> m_draw_items;
    VskInt          m_draw_coord_system;
    VskInt          m_draw_color;
    VskInt          m_draw_fill_color;
    VskDouble       m_draw_scale;
    VskWord         m_draw_line_style;
    VskString       m_draw_tile;
    VskPointD       m_last_point;

    VskDrawEngine() { reset(); }
    bool draw_item(const VskDrawItem& item);
    void reset();

protected:
    VskPointD map_draw_delta(VskPointD pt, VskPointD delta);
    void update_LP(const VskDrawItem& item, VskPointD pt1);
};

// SCREENを実行すると、VskDrawEngineは初期状態になる。
