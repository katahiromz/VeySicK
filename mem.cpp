#include "VeySicK.h"
#include "mem.h"
#include "eat.h"
#include <algorithm>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
// simple memory model - 単純なメモリーブロック

// アドレスがメモリーブロックに含まれているかどうか？
bool VskSimpleMemoryBlock::includes(VskAddr addr, VskMemSize size) const
{
    return (base_addr() <= addr) && (addr + size <= base_addr() + m_size);
}

// メモリーブロックからの１バイト読み込みを行う
bool VskSimpleMemoryBlock::read(VskByte *ptr, VskAddr addr) const
{
    return read(ptr, addr, 1);
}

// メモリーブロックへの１バイト書き込みを行う
bool VskSimpleMemoryBlock::write(const VskByte *ptr, VskAddr addr)
{
    return write(ptr, addr, 1);
}

// メモリーブロックからの読み込みを行う
bool VskSimpleMemoryBlock::read(VskByte *ptr, VskAddr addr, VskMemSize size) const
{
    if (!includes(addr, size))
        return false;
    assert(m_ptr);
    std::memcpy(ptr, &m_ptr[addr - base_addr()], size);
    return true;
}

// メモリーブロックへの書き込みを行う
bool VskSimpleMemoryBlock::write(const VskByte *ptr, VskAddr addr, VskMemSize size)
{
    if (!includes(addr, size))
        return false;
    assert(m_ptr);
    std::memcpy(&m_ptr[addr - base_addr()], ptr, size);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// strings - 文字列群

#define VSK_STRING_AREA_ADDR 0x600 // 文字列格納エリアへのアドレス(実機とは異なる)
#define VSK_STRING_AREA_SIZE (1024 * 1024) // 文字列格納エリアのサイズ(実機とは異なる)

// 文字列領域
static VskByte vsk_str_area[VSK_STRING_AREA_SIZE] = { 0 };
std::shared_ptr<VskStrMemoryBlock> vsk_str_block;

VskStrMemoryBlock::VskStrMemoryBlock(VskMachineState *state) : m_state(state)
{
    m_ptr = vsk_str_area;
    m_size = sizeof(vsk_str_area);
    m_addr = VSK_STRING_AREA_ADDR;
    // EATマスターの初期化
    EAT::init_master(vsk_str_area, sizeof(vsk_str_area));
}

// 文字列を追加する
VskAddr vsk_str_add(const VskString& str)
{
    auto size = (str.size() + 1) * sizeof(char);
    auto *master = EAT::master_from_image(vsk_str_area);
    void *ptr = master->malloc_(size);
    if (!ptr)
        return 0; // 確保できなかった

    // 格納
    std::memcpy(ptr, str.c_str(), size);
    return VskAddr(VSK_STRING_AREA_ADDR + master->offset_from_ptr(ptr));
}

// 文字列を削除する
bool vsk_str_delete(void *ptr)
{
    auto *master = EAT::master_from_image(vsk_str_area);
    master->free_(ptr); // 削除
    return true; // 成功
}

// 文字列を削除する
bool vsk_str_delete(VskAddr addr)
{
    if (!vsk_str_block->includes(addr, 1))
        return false; // 失敗

    auto offset = addr - VSK_STRING_AREA_ADDR;
    auto *master = EAT::master_from_image(vsk_str_area);
    void *ptr = master->ptr_from_offset(offset);
    return vsk_str_delete(ptr);
}

//////////////////////////////////////////////////////////////////////////////
// variables - 変数群

#define VSK_8801_VAR_AREA_ADDR 0x8400 // 変数格納エリアへのアドレス(実機とは異なる)
#define VSK_9801_VAR_AREA_ADDR 0x10000 // 変数格納エリアへのアドレス(実機とは異なる)
#define VSK_VAR_AREA_SIZE 0xC00 // 変数格納エリアのサイズ(実機とは異なる)

// 変数の定義
std::shared_ptr<VskVarMap> vsk_vars_map;

// 変数領域
static VskByte vsk_var_area[VSK_VAR_AREA_SIZE] = { 0 };
std::shared_ptr<VskVarMemoryBlock> vsk_vars_block;

// ベースアドレスを返す
VskAddr VskVarMemoryBlock::base_addr() const
{
    return (m_state->m_machine_mode == VSK_MACHINE_MODE_8801) ? VSK_8801_VAR_AREA_ADDR : VSK_9801_VAR_AREA_ADDR;
}

VskVarMemoryBlock::VskVarMemoryBlock(VskMachineState *state) : m_state(state)
{
    m_ptr = vsk_var_area;
    m_size = sizeof(vsk_var_area);
    m_addr = base_addr();
    // EATマスターの初期化
    EAT::init_master(vsk_var_area, sizeof(vsk_var_area));
}

// ある文字から始まる変数名のデフォルトの型をセットする
void vsk_set_def_type(VskByte ch, VskType type)
{
    if (vsk_isalpha(ch))
    {
        ch = vsk_toupper(ch);
        vsk_machine->m_state->def_var_types[ch - 'A'] = type;
    }
}

// 変数名の型を取得する(タイプゼロ)
VskType vsk_var_get_type_0(const VskString& name)
{
    // 変数名は空ではないはず
    assert(name.size());
    if (name.empty())
        return VSK_TYPE_SINGLE;

    // 変数名に応じた型を返す
    auto type = name[name.size() - 1];
    if (type == VSK_TYPE_ARRAY && name.size() > 2)
        type = name[name.size() - 2];

    switch (type)
    {
    case VSK_TYPE_SINGLE:
    case VSK_TYPE_DOUBLE:
    case VSK_TYPE_INTEGER:
    case VSK_TYPE_STRING:
    case VSK_TYPE_LONG:
        return type;
    }
    return 0;
}

// 変数名の型を取得する。必要ならdef_var_typesを使用する
VskType vsk_var_get_type(const VskString& name)
{
    VskType type = vsk_var_get_type_0(name);
    if (type)
        return type;
    type = vsk_machine->m_state->def_var_types[name[0] - 'A'];
    return type ? type : VSK_TYPE_SINGLE;
}

// 型付き変数名を取得する
VskString vsk_var_get_typed_name(const VskString& name)
{
    // 変数名は空ではないはず
    assert(!name.empty());
    if (name.empty())
        return name;

    // 変数名を大文字にする
    auto typed_name = name;
    vsk_upper(typed_name);

    // 変数名に型を付ける
    auto type = typed_name[typed_name.size() - 1];
    switch (type)
    {
    case VSK_TYPE_SINGLE:
    case VSK_TYPE_DOUBLE:
    case VSK_TYPE_INTEGER:
    case VSK_TYPE_STRING:
    case VSK_TYPE_LONG:
        break;
    case VSK_TYPE_ARRAY:
        break;
    default:
        if (vsk_isalpha(type))
            type = vsk_machine->m_state->def_var_types[typed_name[0] - 'A'];
        else
            type = 0;
        if (!type)
            type = VSK_TYPE_SINGLE;
        typed_name += type;
        break;
    }

    return typed_name;
}

// 配列変数名を取得する
VskString vsk_var_get_typed_name(const VskString& name, bool is_array)
{
    assert(!name.empty());
    auto typed_name = vsk_var_get_typed_name(name);
    assert(!typed_name.empty());
    auto type = typed_name[typed_name.size() - 1];
    if (is_array && type != VSK_TYPE_ARRAY)
        typed_name += VSK_TYPE_ARRAY;
    return typed_name;
}

// 変数を探す
VskVarDescPtr vsk_var_find(const VskString& name, bool is_array)
{
    // 型付き変数名を取得する
    auto typed_name = vsk_var_get_typed_name(name, is_array);

    // 探す
    auto it = vsk_vars_map->find(typed_name);
    if (it == vsk_vars_map->end())
        return nullptr; // 見つからなかった

    return it->second; // 見つかった
}

// 変数は配列か？
bool vsk_var_is_array(const VskString& name)
{
    // 型付き変数名を取得する
    auto typed_name = vsk_var_get_typed_name(name, true);
    // 変数を探す
    auto var_desc = vsk_var_find(typed_name, true);
    if (!var_desc)
        return false; // 見つからなかった
    return !var_desc->m_dimension.empty();
}

// 変数の次元を取得
VskIndexList vsk_var_get_dimension(const VskString& name)
{
    // 変数を探す
    auto var_desc = vsk_var_find(name, true);
    if (!var_desc)
        return { }; // 見つからなかった
    return var_desc->m_dimension;
}

// 変数を削除する
bool vsk_var_delete(const VskString& name, bool is_array)
{
    // 型付き変数名を取得する
    VskString typed_name = vsk_var_get_typed_name(name, is_array);

    // 変数を探す
    auto var_desc = vsk_var_find(typed_name, is_array);
    if (!var_desc)
        return false; // 見つからなかった

    auto offset = var_desc->m_offset;
    if (!offset) // ヒープ版か？
    {
        vsk_vars_map->erase(typed_name);
        return true;
    }

    // イメージ版
    auto *master = EAT::master_from_image<size_t>(vsk_var_area);
    auto ptr = master->ptr_from_offset(offset);
    EAT::ENTRY<size_t> *entry = master->fetch_entry(ptr);
    if (!entry)
        return false; // 有効ではない

    // 文字列の場合、文字列データも消す
    if (var_desc->m_type == VSK_TYPE_STRING)
    {
        auto *str_desc = reinterpret_cast<VskStringDesc *>(ptr);
        VskIndex total_count = var_desc->get_total_count();
        for (VskIndex i = 0; i < total_count; ++i)
            vsk_str_delete(str_desc[i].m_addr);
    }

    // 見つかった。削除
    entry->invalidate();
    vsk_vars_map->erase(typed_name);
    return true;
}

// 変数へのポインタを取得する
void *vsk_var_get_ptr(const VskString& name, const VskIndexList& dimension)
{
    // 必要な情報を取得
    auto typed_name = vsk_var_get_typed_name(name, dimension.size());
    auto type = vsk_var_get_type(typed_name);
    auto type_size = vsk_get_type_size(type);

    // 変数を探す
    auto var_desc = vsk_var_find(typed_name, dimension.size());
    if (!var_desc)
        return nullptr; // 見つからない

    // 添え字を解決する
    VskIndex total_index = 0;
    vsk_get_total_index(total_index, *var_desc, dimension);

    auto offset = var_desc->m_offset;
    if (offset == 0) // ヒープ版？
    {
        if (type == VSK_TYPE_STRING)
            return &var_desc->m_strs[total_index];
        else
            return &var_desc->m_data[total_index * type_size];
    }

    // イメージ版
    auto *master = EAT::master_from_image<size_t>(vsk_var_area);
    auto ptr = master->ptr_from_offset(offset);
    if (!master->fetch_entry(ptr))
        return nullptr; // 有効ではない

    return ptr;
}

// 変数を宣言する
bool vsk_var_declare(const VskString& name, const VskIndexList& dimension)
{
    // 必要な情報を取得
    auto typed_name = vsk_var_get_typed_name(name, dimension.size());
    auto type = vsk_var_get_type(typed_name);
    auto type_size = vsk_get_type_size(type);

    // 変数を探す
    if (vsk_var_find(typed_name, dimension.size()))
    {
        vsk_error(VSK_ERR_DUPLICATE_DEFINE);
        return false; // すでにある
    }

    // 要素の個数を計算する
    VskIndex total_count = 1;
    for (auto& dim : dimension)
        total_count *= dim;

    // vsk_vars_mapに追加
    auto var_desc = std::make_shared<VskVarDesc>();
    var_desc->m_type = type;
    var_desc->m_dimension = dimension;
    var_desc->m_offset = 0;
    var_desc->m_typed_name = typed_name;
    if (type == VSK_TYPE_STRING)
        var_desc->m_strs.resize(total_count);
    else
        var_desc->m_data.resize(type_size * total_count, '\0');
    (*vsk_vars_map)[typed_name] = var_desc;

    return true;
}

// 変数名から変数ポインタを取得
VskAddr vsk_var_get_varptr(const VskString& name, const VskIndexList& dimension)
{
    // 必要な情報を取得
    auto typed_name = vsk_var_get_typed_name(name, dimension.size());
    auto type = vsk_var_get_type(typed_name);
    auto type_size = vsk_get_type_size(type);

    // 変数を探す
    auto var_desc = vsk_var_find(name, dimension.size());
    if (!var_desc)
        return 0; // 見つからない

    // 添え字を解決する
    VskIndex total_index;
    if (!vsk_get_total_index(total_index, *var_desc, dimension))
        return 0; // 添え字が無効

    auto offset = var_desc->m_offset;
    if (offset != 0) // イメージ版？
    {
        auto *master = EAT::master_from_image<size_t>(vsk_var_area);
        auto ptr = master->ptr_from_offset(offset);
        auto *entry = master->fetch_entry(ptr);
        if (!entry)
            return 0; // 有効ではない

        return VSK_STRING_AREA_ADDR + offset + total_index * type_size;
    }

    // イメージに確保
    auto total_count = var_desc->get_total_count();
    auto *master = EAT::master_from_image<size_t>(vsk_var_area);
    auto ptr = master->malloc_(total_count * type_size);
    if (!ptr)
    {
        vsk_error(VSK_ERR_NO_MEMORY);
        return 0; // メモリー不足
    }
    var_desc->m_offset = offset = master->offset_from_ptr(ptr);
    assert(offset != 0);

    if (type == VSK_TYPE_STRING) // 文字列の場合は文字列領域が必要
    {
        for (VskIndex i = 0; i < total_count; ++i)
        {
            auto& str = var_desc->m_strs[i];
            VskAddr str_addr = vsk_str_add(str);
            if (!str_addr)
            {
                master->free_(ptr);
                vsk_error(VSK_ERR_NO_MEMORY);
                return false; // 失敗
            }

            auto& str_desc = reinterpret_cast<VskStringDesc *>(ptr)[i];
            str_desc.m_length = VskByte(str.size() < VSK_MAX_STR_LEN ? str.size() : VSK_MAX_STR_LEN);
            str_desc.m_relocation = 1; // VeySicKでは常に非ゼロ
            str_desc.m_addr = VskWord(str_addr);
        }
        var_desc->m_strs.clear();
    }
    else
    {
        std::memcpy(ptr, var_desc->m_data.data(), total_count * type_size);
        var_desc->m_data.clear();
    }

    return VSK_STRING_AREA_ADDR + offset + total_index * type_size;
}

// 変数を追加する
bool vsk_var_set_value(const VskString& name, const VskIndexList& dimension, const void *data)
{
    // 必要な情報を取得
    auto typed_name = vsk_var_get_typed_name(name, dimension.size());
    auto type = vsk_var_get_type(typed_name);
    auto type_size = vsk_get_type_size(type);

    // 変数を探す
    auto var_desc = vsk_var_find(typed_name, dimension.size());
    if (var_desc) // 見つかった？
    {
        // 添え字を解決する
        VskIndex total_index;
        if (!vsk_get_total_index(total_index, *var_desc, dimension))
            return false; // 添え字が無効

        auto offset = var_desc->m_offset;
        if (!offset) // ヒープ版？
        {
            if (type == VSK_TYPE_STRING)
                var_desc->m_strs[total_index] = *(VskString*)data;
            else
                std::memcpy(&var_desc->m_data[total_index * type_size], data, type_size);
            return true;
        }

        // イメージ版
        auto *master = EAT::master_from_image<size_t>(vsk_var_area);
        auto ptr = master->ptr_from_offset(offset);
        auto *entry = master->fetch_entry(ptr);
        if (!entry)
            return false; // 有効ではない

        if (type == VSK_TYPE_STRING) // 文字列か？
        {
            // まず削除
            auto *str_desc = reinterpret_cast<VskStringDesc *>(ptr);
            vsk_str_delete(str_desc[total_index].m_addr);
            // そして追加
            VskString& str = *(VskString*)data;
            auto str_addr = vsk_str_add(str);
            str_desc->m_length = VskByte((str.size() > VSK_MAX_STR_LEN) ? VSK_MAX_STR_LEN : str.size());
            str_desc->m_addr = VskWord(str_addr);
            return true;
        }

        std::memcpy(&var_desc->m_data[total_index * type_size], data, type_size);
        return true;
    }

    if (dimension.size() == 0)
    {
        vsk_var_declare(typed_name, {});
        return vsk_var_set_value(typed_name, dimension, data);
    }
    if (dimension.size() == 1 && dimension[0] <= 10)
    {
        vsk_var_declare(typed_name, { 10 });
        return vsk_var_set_value(typed_name, dimension, data);
    }

    vsk_error(VSK_ERR_BAD_INDEX);
    return false; // 失敗
}

// 変数の値を取得する
bool vsk_var_get_value(const VskString& name, void **pptr, const VskIndexList& indices)
{
    *pptr = nullptr;

    // 必要な情報を取得
    auto typed_name = vsk_var_get_typed_name(name, indices.size());
    auto type = vsk_var_get_type(typed_name);
    auto type_size = vsk_get_type_size(type);

    // 変数を探す
    auto var_desc = vsk_var_find(typed_name, indices.size());
    if (!var_desc)
    {
        return false; // 見つからなかった
    }

    // 添え字を解決する
    VskIndex total_index;
    if (!vsk_get_total_index(total_index, *var_desc, indices))
    {
        return false;
    }

    auto offset = var_desc->m_offset;
    if (!offset)
    {
        if (type == VSK_TYPE_STRING)
        {
            *pptr = new VskString(var_desc->m_strs[total_index]);
        }
        else
        {
            *pptr = &var_desc->m_data[total_index * type_size];
        }
        return true;
    }

    // ポインタを取得
    auto *master1 = EAT::master_from_image(vsk_var_area);
    auto *ptr1 = master1->ptr_from_offset(offset);
    if (!ptr1)
        return false; // 失敗

    VskByte *ptr2 = reinterpret_cast<VskByte *>(ptr1) + total_index * type_size;

    // 文字列以外なら成功
    if (var_desc->m_type != VSK_TYPE_STRING)
    {
        *pptr = ptr2;
        return true;
    }

    // 文字列の場合は、VskStringDescをたどる
    auto *str_desc = reinterpret_cast<VskStringDesc *>(ptr2);
    assert(str_desc->m_relocation != 0);
    auto addr = str_desc->m_addr;
    auto *master2 = EAT::master_from_image(vsk_str_area);
    char *ptr3 = reinterpret_cast<char *>(master2->ptr_from_offset(addr - VSK_STRING_AREA_ADDR));
    assert(ptr3);
    if (ptr3)
    {
        if (str_desc->m_length >= VSK_MAX_STR_LEN)
            *pptr = new VskString(ptr3, VSK_MAX_STR_LEN + std::strlen(ptr3 + VSK_MAX_STR_LEN));
        else
            *pptr = new VskString(ptr3, str_desc->m_length);
    }

    return true;
}

// （多重）配列内部の要素数
VskIndex VskVarDesc::get_total_count() const
{
    if (m_dimension.size() == 0)
        return 1;
    VskIndex ret = 1;
    for (auto& d : m_dimension)
        ret *= d;
    return ret;
}

VskIndex VskVarDesc::get_total_size() const
{
    return get_total_count() * vsk_get_type_size(m_type);
}

// 添え字を解決する
bool vsk_get_total_index(VskIndex& total_index, VskVarDesc& desc, const VskIndexList& index_list)
{
    total_index = 0;

    if (index_list.size() != desc.m_dimension.size())
        return false;

    if (index_list.empty())
        return true;

    for (VskIndex index0 = 0; index0 < index_list.size(); ++index0)
    {
        VskIndex factor = index_list[index0];
        for (VskIndex index1 = index0 + 1; index1 < index_list.size(); ++index1)
        {
            if (index_list[index1] >= desc.m_dimension[index1])
                return false;
            factor *= desc.m_dimension[index1];
        }
        total_index += factor;
    }

    if (total_index >= desc.get_total_count())
    {
        vsk_error(VSK_ERR_BAD_INDEX);
        return false;
    }

    return true;
}

// 変数をすべてクリアする
void vsk_var_clear_all(void)
{
    EAT::init_master(vsk_var_area, sizeof(vsk_var_area));
    EAT::init_master(vsk_str_area, sizeof(vsk_str_area));
    vsk_vars_map = std::make_shared<VskVarMap>();
    for (auto& byte : VSK_STATE()->def_var_types)
        byte = 0;
    VSK_STATE()->m_option_base = -1;
}

//////////////////////////////////////////////////////////////////////////////
// memory model

// メモリーモデルからの読み込みを行う
bool VskMemoryModel::read(VskByte *ptr, VskAddr addr, VskMemSize size) const
{
    bool ok = true;
    for (VskAddr ib = 0; ib < size; ++ib)
    {
        VskByte byte;
        if (vsk_machine->special_memory_read(&byte, addr + ib))
        {
            ptr[ib] = byte;
            continue;
        }

        for (auto& block : m_blocks)
        {
            if (block->includes(addr + ib, 1))
            {
                if (!block->read(&ptr[ib], addr + ib))
                    ok = false;
                break;
            }
        }
        if (!ok)
            break;
    }

    return ok;
}

// メモリーモデルへの書き込みを行う
bool VskMemoryModel::write(const VskByte *ptr, VskAddr addr, VskMemSize size)
{
    bool ok = true;
    for (VskAddr ib = 0; ib < size; ++ib)
    {
        for (auto& block : m_blocks)
        {
            if (block->includes(addr + ib, 1))
            {
                if (!block->write(&ptr[ib], addr + ib))
                    ok = false;
                break;
            }
        }
    }
    return ok;
}

// メモリーモデルへメモリーブロックを追加する
bool VskMemoryModel::add_block(VskMemoryBlockBase *block)
{
    m_blocks.push_back(block);
    return true;
}

// メモリーモデルからメモリーブロックを削除する
void VskMemoryModel::remove_block(VskMemoryBlockBase *block)
{
    auto it = std::find(m_blocks.begin(), m_blocks.end(), block);
    if (it != m_blocks.end())
        m_blocks.erase(it);
}
