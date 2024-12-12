#pragma once

#include "types.h"

//////////////////////////////////////////////////////////////////////////////
// variables - 変数群

// 変数記述子
struct VskVarDesc : VskObject
{
    VskType                 m_type;
    VskIndexList            m_dimension;
    VskAddr                 m_offset;
    VskString               m_typed_name;
    VskString               m_data;
    std::vector<VskString>  m_strs;
    bool                    m_common = false;

    VskIndex get_total_count() const;
    VskIndex get_total_size() const;
};
typedef std::shared_ptr<VskVarDesc> VskVarDescPtr;

// 文字列記述子
struct VskStringDesc
{
    VskByte  m_length;      // 256以上ならば文字列はヌル終端
    VskByte  m_relocation;
    VskWord  m_addr;
};

// 変数を宣言する
bool vsk_var_declare(const VskString& name, const VskIndexList& dimension);
// 変数は配列か？
bool vsk_var_is_array(const VskString& name);
// 変数の次元を取得
VskIndexList vsk_var_get_dimension(const VskString& name);
// 変数を削除する
bool vsk_var_delete(const VskString& name, bool is_array = false);
// 変数を探す
std::shared_ptr<VskVarDesc> vsk_var_find(const VskString& name, bool is_array = false);
// 変数の値を取得する
bool vsk_var_get_value(const VskString& name, void **pptr, const VskIndexList& indices);
// 変数の値をセットする
bool vsk_var_set_value(const VskString& name, const VskIndexList& dimension, const void *data);
// 変数名から変数ポインタを取得
VskAddr vsk_var_get_varptr(const VskString& name, const VskIndexList& dimension);
// 変数へのポインタを取得する
void *vsk_var_get_ptr(const VskString& name, const VskIndexList& dimension, bool is_array = false);
// 変数名のデフォルトの型をセットする
void vsk_set_def_type(VskByte ch, VskType type);
// 型付き変数名を取得する
VskString vsk_var_get_typed_name(const VskString& name);
// 配列変数名を取得する
VskString vsk_var_get_typed_name(const VskString& name, bool is_array);
// 変数名の型を取得する
VskType vsk_var_get_type(const VskString& name);
// 変数名の型を取得する(タイプゼロ)
VskType vsk_var_get_type_0(const VskString& name);
// 変数をすべてクリアする
void vsk_var_clear_all(void);
// COMMONではない変数をすべてクリアする
void vsk_var_clear_non_common(void);
// 添え字を解決する
bool vsk_get_total_index(VskIndex& total_index, VskVarDesc& desc, const VskIndexList& index_list);

// 変数の定義
typedef std::unordered_map<std::string, VskVarDescPtr> VskVarMap;
extern std::shared_ptr<VskVarMap> vsk_vars_map;

//////////////////////////////////////////////////////////////////////////////
// VskMemoryBlockBase --- メモリーブロックの抽象クラス

struct VskMemoryBlockBase : public VskObject
{
    VskMemoryBlockBase() { }
    virtual bool includes(VskAddr addr, VskMemSize size) const { return false; }
    virtual bool read(VskByte *ptr, VskAddr addr) const { return false; }
    virtual bool write(const VskByte *ptr, VskAddr addr) { return false; }
    virtual bool read(VskByte *ptr, VskAddr addr, VskMemSize size) const { return false; }
    virtual bool write(const VskByte *ptr, VskAddr addr, VskMemSize size) { return false; }

private:
    VskMemoryBlockBase(const VskMemoryBlockBase& block) = delete;
    VskMemoryBlockBase& operator=(const VskMemoryBlockBase& block) = delete;
};

//////////////////////////////////////////////////////////////////////////////
// VskSimpleMemoryBlock --- 単純なメモリーブロック

struct VskSimpleMemoryBlock : VskMemoryBlockBase
{
    VskAddr m_addr = 0;
    VskMemSize m_size = 0;
    VskByte *m_ptr = NULL;
    bool m_is_alloc = false;

    VskSimpleMemoryBlock() { }
    VskSimpleMemoryBlock(VskAddr addr, VskMemSize size, VskByte *ptr)
        : m_addr(addr)
        , m_size(size)
        , m_ptr(ptr)
        , m_is_alloc(false)
    {
    }
    VskSimpleMemoryBlock(VskAddr addr, VskMemSize size)
        : m_addr(addr)
        , m_size(size)
        , m_ptr(new VskByte[size])
        , m_is_alloc(true)
    {
        assert(m_ptr);
    }
    ~VskSimpleMemoryBlock()
    {
        if (m_is_alloc)
        {
            delete[] m_ptr;
            m_ptr = nullptr;
        }
    }

    void clear()
    {
        std::memset(m_ptr, 0, m_size);
    }

          VskByte& operator[](VskDword index)       { return m_ptr[index]; }
    const VskByte& operator[](VskDword index) const { return m_ptr[index]; }

    virtual VskAddr base_addr() const { return m_addr; }
    bool includes(VskAddr addr, VskMemSize size) const override;
    bool read(VskByte *ptr, VskAddr addr) const override;
    bool write(const VskByte *ptr, VskAddr addr) override;
    bool read(VskByte *ptr, VskAddr addr, VskMemSize size) const override;
    bool write(const VskByte *ptr, VskAddr addr, VskMemSize size) override;
};

//////////////////////////////////////////////////////////////////////////////
// VskMemoryModel --- メモリーモデル

struct VskMemoryModel : public VskObject
{
    // ブロック群を保持
    std::vector<VskMemoryBlockBase *> m_blocks;

    // メモリーブロックを追加
    bool add_block(VskMemoryBlockBase *block);
    // メモリーブロックを削除
    void remove_block(VskMemoryBlockBase *block);

    // メモリーの読み込み
    virtual bool read(VskByte *ptr, VskAddr addr, VskMemSize size) const;
    // メモリーへの書き込み
    virtual bool write(const VskByte *ptr, VskAddr addr, VskMemSize size);
};

//////////////////////////////////////////////////////////////////////////////
