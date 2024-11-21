#include "turtle.h"
#include "encoding.h"
#include "draw_algorithm.h"
#include "coreapi.h"

// タートル項目を展開する
static bool vsk_expand_turtle_items(std::vector<VskTurtleItem>& items)
{
retry:;
    size_t k = VskString::npos;
    int level = 0, repeat = 0;
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].m_subcommand == "RP") { // REPEAT (繰り返し)
            if (auto ast = vsk_eval_text(items[i].m_params[0])) {
                repeat = vsk_round(ast->value());
                if (repeat < 0)
                    return false;
            }
        }
        if (items[i].m_subcommand == "[") { // 繰り返しの始まり
            k = i;
            ++level;
        }
        if (items[i].m_subcommand == "]") { // 繰り返しの終わり
            --level;
            if ((level == 0) && (repeat > 0)) {
                std::vector<VskTurtleItem> sub(items.begin() + k + 1, items.begin() + i);
                std::vector<VskTurtleItem> children;
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
} // vsk_expand_turtle_items

// 文字列からタートル項目群を取得
bool vsk_get_turtle_items_from_string(std::vector<VskTurtleItem>& items, const VskString& str)
{
    items.clear();

    VskString subcommand;
    VskTurtleItem item;
    VskString param;

    int status = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        char ch = vsk_toupper(str[i]);
        if (vsk_isblank(ch))
            continue;
        switch (status) {
        case 0:
            if (ch == ';')
                continue;
            if (ch == '[') { // 繰り返しの始まり
                item.m_subcommand = "[";
                items.push_back(item);
                item.clear();
                continue;
            }
            if (ch == ']') { // 繰り返しの終わり
                item.m_subcommand = "]";
                items.push_back(item);
                item.clear();
                continue;
            }
            if (vsk_isupper(ch)) { // サブコマンドみたいか？
                subcommand.push_back(ch);
                if (subcommand.size() > 2) {
                    return false;
                }
            }
            if (subcommand.size() == 2) { // サブコマンドの名前の長さが2か？
                // コマンドに応じて状態と項目を更新
                item.m_subcommand = subcommand;
                if (subcommand == "FD" || subcommand == "BK" || subcommand == "SX" || subcommand == "SY" ||
                    subcommand == "LT" || subcommand == "RT" || subcommand == "HD" || subcommand == "CP" ||
                    subcommand == "PC" || subcommand == "RP")
                {
                    status = 1;
                } else if (subcommand == "MV") {
                    status = 2;
                } else if (subcommand == "PD" || subcommand == "PU" || subcommand == "ST" || subcommand == "HT") {
                    items.push_back(item);
                    item.clear();
                } else {
                    assert(0);
                    return false;
                }
                subcommand.clear();
            }
            break;
        case 1: case 2: // サブコマンドに1個か2個の引数があるか？
            param.clear();
            if (ch == '(') { // 変数か？
                int level = 1;
                for (;;) {
                    ch = str[++i];
                    if (ch == 0)
                        break;
                    if (ch == '(') {
                        ++level;
                    } else if (ch == ')') {
                        if (--level == 0)
                            break;
                    }
                    if (!vsk_isblank(ch))
                        param.push_back(ch);
                }
            } else if (vsk_isdigit(ch) || (ch == '-') || (ch == '+') || (ch == '.')) { // 数値か？
                do {
                    if (!vsk_isblank(ch))
                        param.push_back(ch);
                    ch = str[++i];
                } while (vsk_isdigit(ch) || vsk_isblank(ch) || (ch == '-') || (ch == '+') || (ch == '.'));
                if (ch != ',')
                    --i;
            } else {
                return false;
            }

            // パラメータを追加
            item.m_params.emplace_back(param);

            // 初期状態になったら項目を追加
            if (--status == 0) {
                items.push_back(item);
                item.clear();
            }
            break;

        default:
            assert(0);
            return false;
        }
    }

    if (status == 2)
    {
        assert(0);
        return false;
    }

    if (status == 1)
    {
        if (item.m_subcommand == "LT" || item.m_subcommand == "RT")
            item.m_params.emplace_back("90");

        if (--status == 0)
            items.push_back(item);
    }

    return vsk_expand_turtle_items(items);
} // vsk_get_turtle_items_from_string

void VskTurtleEngine::reset()
{
    m_is_shown = false;
    m_pen_down = false;
    m_direction_in_degree = 0;
    m_pen_color = 7;
    m_pos_adjustment = true;
    m_last_ref = { -1, -1 };
    m_is_init = false;
}

// タートルを表示・非表示
void VskTurtleEngine::show(bool do_show)
{
    m_is_shown = do_show;
}

// ペンを下ろす、上げる
void VskTurtleEngine::pen_down(bool down)
{
    m_pen_down = down;
}

// スクリーン座標でタートルの位置を取得
VskPointD VskTurtleEngine::get_pos_in_screen() const
{
    return vsk_machine->world_to_screen(m_last_ref);
}

// パラメータを取得
VskAstPtr vsk_get_turtle_param(const VskTurtleItem& item, size_t index)
{
    if (index >= item.m_params.size() || item.m_params[index].empty())
        return nullptr;
    return vsk_eval_text(item.m_params[index]);
} // vsk_get_play_param

// 最終点を更新する
void VskTurtleEngine::update_LP(const VskPointD& pt_in_screen)
{
    m_last_ref = pt_in_screen;
    VSK_STATE()->m_last_ref = vsk_machine->screen_to_world(pt_in_screen);
}

// タートルの向きをラジアンで返す
VskDouble VskTurtleEngine::get_turtle_direction_in_radian() const
{
    return -(m_direction_in_degree - 90) * M_PI / 180.0;
}

// タートルエンジンのしょおきか
void VskTurtleEngine::init()
{
    if (!m_is_init) {
        m_last_ref.m_x = (VSK_STATE()->m_viewport.m_x0 + VSK_STATE()->m_viewport.m_x1) / 2.0;
        m_last_ref.m_y = (VSK_STATE()->m_viewport.m_y0 + VSK_STATE()->m_viewport.m_y1) / 2.0;
        m_is_init = true;
    }
}

#define PT2INTS(pt) vsk_round((pt).m_x), vsk_round((pt).m_y)

// タートル項目を描画する
bool VskTurtleEngine::turtle_item(const VskTurtleItem& item)
{
    init();

    if (item.m_subcommand == "FD") { // FORWARD (前に進む)
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            auto d0 = ast0->value();
            auto radian = get_turtle_direction_in_radian();
            VskPointD pt0 = get_pos_in_screen();
            VskPointD pt1;
            if (m_pos_adjustment && VSK_STATE()->is_height_200()) {
                pt1 = { pt0.m_x + d0 * std::cos(radian) * 2, pt0.m_y - d0 * std::sin(radian) };
            } else {
                pt1 = { pt0.m_x + d0 * std::cos(radian)    , pt0.m_y - d0 * std::sin(radian) };
            }
            if (m_pen_down) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), m_pen_color, 0xFFFF);
            }
            update_LP(pt1);
            return true;
        }
    } else if (item.m_subcommand == "BK") { // BACK (戻る)
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            auto d0 = ast0->value();
            auto radian = get_turtle_direction_in_radian();
            VskPointD pt0 = get_pos_in_screen();
            VskPointD pt1;
            if (m_pos_adjustment && VSK_STATE()->is_height_200()) {
                pt1 = { pt0.m_x - d0 * std::cos(radian) * 2, pt0.m_y + d0 * std::sin(radian) };
            } else {
                pt1 = { pt0.m_x - d0 * std::cos(radian)    , pt0.m_y + d0 * std::sin(radian) };
            }
            if (m_pen_down) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), m_pen_color, 0xFFFF);
            }
            update_LP(pt1);
            return true;
        }
    } else if (item.m_subcommand == "MV") { // 移動(MOVE)、向きは変わらない
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            if (auto ast1 = vsk_get_turtle_param(item, 1)) {
                update_LP({ ast0->value(), ast1->value() });
                return true;
            }
        }
    } else if (item.m_subcommand == "SX") { // X方向に移動、向きは変わらない
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            update_LP({ ast0->value(), get_pos_in_screen().m_x });
            return true;
        }
    } else if (item.m_subcommand == "SY") { // Y方向に移動、向きは変わらない
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            update_LP({ get_pos_in_screen().m_x, ast0->value() });
            return true;
        }
    } else if (item.m_subcommand == "HD") { // タートルの向きをセット（単位は度）
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            m_direction_in_degree = ast0->value();
            return true;
        }
    } else if (item.m_subcommand == "LT") { // 現在の向きから左に自転する（単位は度）
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            m_direction_in_degree -= ast0->value();
            return true;
        }
    } else if (item.m_subcommand == "RT") { // 現在の向きから右に自転する（単位は度）
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            m_direction_in_degree += ast0->value();
            return true;
        }
    } else if (item.m_subcommand == "CP") { // タートルの位置補正
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            auto i0 = vsk_round(ast0->value());
            if (i0 == 0) {
                m_pos_adjustment = false;
                return true;
            } else if (i0 == 1) {
                m_pos_adjustment = true;
                return true;
            }
        }
    } else if (item.m_subcommand == "PD") { // タートルのペンを下げる
        pen_down(true);
        return true;
    } else if (item.m_subcommand == "PU") { // タートルのペンを上げる
        pen_down(false);
        return true;
    } else if (item.m_subcommand == "PC") { // タートルのペンの色
        if (auto ast0 = vsk_get_turtle_param(item, 0)) {
            auto i0 = vsk_round(ast0->value());
            if (vsk_machine->is_valid_color(i0)) {
                m_pen_color = i0;
                return true;
            }
        }
    } else if (item.m_subcommand == "HT") { // タートルを消す
        show(false);
        return true;
    } else if (item.m_subcommand == "ST") { // タートルを表示する
        show(true);
        return true;
    }

    assert(0);
    return false;
} // VskTurtleEngine::turtle_item

// タートルを描画する
void vsk_turtle_draw_cursor(Vsk32BppImage& image)
{
    // 位置と角度を取得
    VskPointD pos = vsk_turtle_pos_in_screen();
    VskDouble direction = vsk_turtle_direction_in_radian();

    // 画面が引き伸ばされているときの対策
    int screen_ratio = 1;
    if (VSK_STATE()->is_height_200()) {
        screen_ratio = 2;
    }

    // タートル図形の頂点を決める
    VskPointD apt[4];
    int radian = 16; // 半径
    apt[0].m_x = pos.m_x + radian * std::cos(direction - M_PI / 2) / 2 * screen_ratio;
    apt[0].m_y = pos.m_y - radian * std::sin(direction - M_PI / 2) / 2;
    apt[1].m_x = pos.m_x + radian * std::cos(direction + M_PI / 2) / 2 * screen_ratio;
    apt[1].m_y = pos.m_y - radian * std::sin(direction + M_PI / 2) / 2;
    apt[2].m_x = pos.m_x + radian * std::cos(direction) * screen_ratio;
    apt[2].m_y = pos.m_y - radian * std::sin(direction);
    apt[3].m_x = pos.m_x + radian * std::cos(direction - M_PI / 2) / 2 * screen_ratio;
    apt[3].m_y = pos.m_y - radian * std::sin(direction - M_PI / 2) / 2;

    // XOR演算でピクセルを描画する
    auto putter = [&](int x, int y) {
        auto pixel = image.get_pixel(x, y);
        image.set_pixel(x, y, 0xFFFFFF ^ pixel);
    };

    int count = sizeof(apt) / sizeof(apt[0]);
    for (int i = 0; i < count; ++i)
    {
        // 線を描く
        int k = (i + 1) % count;
        vsk_draw_line(putter, vsk_round(apt[i].m_x), vsk_round(apt[i].m_y) * screen_ratio,
                              vsk_round(apt[k].m_x), vsk_round(apt[k].m_y) * screen_ratio);
        // XOR演算により、重なった頂点が消えてしまうので対策
        putter(vsk_round(apt[i].m_x), vsk_round(apt[i].m_y) * screen_ratio);
    }
}
