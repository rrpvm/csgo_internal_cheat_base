#pragma once
#include <vector>
#include <string>
#include <exception>
#include <optional>
#include "../Singleton.h"
#include <utility>
class RecvTable;
class ClientClass;
enum SendPropType
{
    DPT_Int = 0,
    DPT_Float,
    DPT_Vector,
    DPT_VectorXY,
    DPT_String,
    DPT_Array,
    DPT_DataTable,
    DPT_Int64,
    DPT_NUMSendPropTypes
};
class RecvProp
{
public:
    char* m_pVarName;
    SendPropType             m_RecvType;
    int                     m_Flags;
    int                     m_StringBufferSize;
    int                     m_bInsideArray;
    const void* m_pExtraData;
    RecvProp* m_pArrayProp;
    void* m_ArrayLengthProxy;
    void* m_ProxyFn;
    void* m_DataTableProxyFn;
    RecvTable* m_pDataTable;
    int                     m_Offset;
    int                     m_ElementStride;
    int                     m_nElements;
    const char* m_pParentArrayPropName;
};
class RecvTable
{
public:

    RecvProp* m_pProps;
    int            m_nProps;
    void* m_pDecoder;
    char* m_pNetTableName;
    bool        m_bInitialized;
    bool        m_bInMainList;
};
struct m_table {
    std::vector<std::pair<RecvProp,m_table> >props;
    std::string table_name;
};
class netvar_manager: public Singleton<netvar_manager> {
public:
    void dump_table(ClientClass* first);
    m_table read_table(RecvTable* table);
    std::vector<m_table>data;
    uintptr_t get_offset(const std::string& table_name, const std::string& sub_table, const std::string& m_offset);
    uintptr_t get_offset(const m_table& table, const std::string& m_offset);
    uintptr_t get_offset(const std::string& main_table, const std::string& m_offset);
    uintptr_t get_offset_g(int table_num,const std::string& m_offset);
    std::optional< m_table> find_child_table(const std::string& table_name, const std::string& sub_table);
private:
    uintptr_t get_offset_g(const std::string& m_offset, const m_table& table);
};