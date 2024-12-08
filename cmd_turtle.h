#pragma once

#include "VeySicK.h"

//////////////////////////////////////////////////////////////////////////////
// VskTurtleItem --- an item of CMD TURTLE

struct VskTurtleItem
{
    VskString               m_subcommand;
    std::vector<VskString>  m_params;

    VskTurtleItem() { clear(); }

    void clear() {
        m_subcommand.clear();
        m_params.clear();
    }
}; // struct VskTurtleItem

bool vsk_get_turtle_items_from_string(std::vector<VskTurtleItem>& items, const VskString& str);

//////////////////////////////////////////////////////////////////////////////
// VskTurtleItem --- CMD TURTLE engine

struct VskTurtleEngine
{
    bool            m_is_shown;
    bool            m_pen_down;
    VskInt          m_pen_color;
    bool            m_pos_adjustment;
    VskSingle       m_direction_in_degree;
    VskPointS       m_last_point_in_screen;
    bool            m_is_init;

    VskTurtleEngine() { reset(); }

    void init();
    bool turtle_item(const VskTurtleItem& item);
    void reset();
    void show(bool do_show);
    void pen_down(bool down);
    VskPointS get_pos_in_screen() const;
    VskSingle get_turtle_direction_in_radian() const;

protected:
    void update_LP(const VskPointS& pt_in_screen);
};

void vsk_turtle_draw_cursor(Vsk32BppImage& image);

//////////////////////////////////////////////////////////////////////////////
