#include "netvars.hpp"
#include "client_class.hpp"
void netvar_manager::dump_table(ClientClass* first)
{
	data.clear();
	do {
		data.emplace_back(read_table(first->m_pRecvTable));
	} while ((first = first->m_pNext));
#if _DEBUG
	int bResultCode = 1;
#endif // 0
}
m_table netvar_manager::read_table(RecvTable* table)
{
	m_table _table;
	_table.table_name = table->m_pNetTableName;
	for (int i = 0; i < table->m_nProps; ++i)
	{
		const RecvProp&  p = table->m_pProps[i];		
		if (p.m_RecvType == DPT_DataTable && p.m_pDataTable && p.m_pDataTable->m_nProps > 0 && strcmp(p.m_pVarName, "baseclass"))
		{
			_table.props.push_back(std::make_pair(p, read_table(p.m_pDataTable)));
		}
		else _table.props.push_back(std::make_pair(p, m_table()));
	}
	return _table;
}
uintptr_t netvar_manager::get_offset(const std::string& table_name, const std::string& sub_table, const std::string& m_offset)
{

	const auto& ch_table = find_child_table(table_name, sub_table);
	if (ch_table.has_value())
		return get_offset(ch_table.value(), m_offset);
	return 0;
}
uintptr_t netvar_manager::get_offset(const m_table& table, const std::string& m_offset)
{
	for (const auto& p : table.props)//15.08 11:13
	{
		if (!strcmp(p.first.m_pVarName, m_offset.c_str()))return p.first.m_Offset;
	}
	return -1;
}
uintptr_t netvar_manager::get_offset(const std::string& main_table, const std::string& m_offset)
{
	for (m_table t : data)
	{
		if (t.table_name == main_table)
		{
			for (unsigned int i = 0; i < t.props.size(); i++)
			{
				const RecvProp& p = t.props.at(i).first;
				if (!strcmp(p.m_pVarName, m_offset.c_str()))return p.m_Offset;
			}
		}
	}
	return -1;
}
uintptr_t netvar_manager::get_offset_g(int table_num,const std::string& m_offset)
{
		uintptr_t offset = get_offset_g(m_offset, data.at(table_num));
		if (offset)return offset;
		return 0;
}
std::optional<m_table> netvar_manager::find_child_table(const std::string& table_name, const std::string& sub_table)
{
	for (const m_table& table : data)
	{
		if (table.table_name != table_name)continue;
		for (const auto& ch : table.props)
		{
			if (ch.second.table_name == sub_table)return std::optional<m_table>(ch.second);
		}
	}
	return std::nullopt;
}
uintptr_t netvar_manager::get_offset_g(const std::string& m_offset, const m_table& table)
{
	for (const std::pair< RecvProp, m_table>& p : table.props)
	{
		if (m_offset == p.first.m_pVarName)return p.first.m_Offset;		
	}
	for (const std::pair< RecvProp, m_table>& p : table.props)
	{
		if (!p.second.table_name.empty())
		{
			uintptr_t offset = table.props.front().first.m_Offset + get_offset_g(m_offset, p.second);
			if (offset)return offset;
		}
	}
}
/*
m_table netvar_manager::read_table(RecvTable* table)
{
	m_table _table;
	_table.table_name = table->m_pNetTableName;
	for (int i = 0; i < table->m_nProps; ++i)
	{
		RecvProp  p = table->m_pProps[i];
		_table.props.push_back(p);
		//if (p.m_pDataTable && strcmp(p.m_pVarName,"baseclass"))_table.childs.push_back(read_table(p.m_pDataTable));
		if (p.m_pDataTable )_table.childs.push_back(read_table(p.m_pDataTable));
	}
	return _table;
}
uintptr_t netvar_manager::get_offset(const std::string& table_name, const std::string& sub_table, const std::string& m_offset)
{
	const auto& ch_table = find_child_table(table_name, sub_table);
	if(ch_table.has_value())
	return get_offset(ch_table.value(),  m_offset);
	return 0;
}

uintptr_t netvar_manager::get_offset(const m_table& table, const std::string& m_offset)
{
	for (const RecvProp& p : table.props)//15.08 11:13
	{
		if (!strcmp(p.m_pVarName, m_offset.c_str()))return p.m_Offset;
	}
	return -1;
}

uintptr_t netvar_manager::get_offset(const std::string& main_table, const std::string& m_offset)
{
	for (m_table t:data)
	{
		if (!strcmp(t.table_name, main_table.c_str()))
		{
			for (unsigned int i = 0; i < t.props.size(); i++)
			{
				const RecvProp& p = t.props.at(i);
				if (!strcmp(p.m_pVarName, m_offset.c_str()))return p.m_Offset;
			}
		}
	}
	return -1;
}

uintptr_t netvar_manager::get_offset_g(const std::string& m_offset)
{
	int ret = 0;
	static int i = 0;
	for (const m_table& d : data)
	{
		i++;
		ret= get_offset_g(m_offset,d);
		if (ret)return ret;
	}
	return 0;
}
std::optional< m_table> netvar_manager::find_child_table(const std::string& table_name, const std::string& sub_table) 
{
	for (const m_table& table : data)
	{
		if (strcmp(table.table_name, table_name.c_str()))continue;
		for (const auto& ch : table.childs)
		{
			if (!strcmp(ch.table_name, sub_table.c_str()))return std::optional<m_table>(ch);
		}
	}
	return std::nullopt;

}
uintptr_t netvar_manager::get_offset_g(const std::string& m_offset, const m_table& table)
{
	for (auto prop : table.props)
	{
		if (!strcmp(prop.m_pVarName, m_offset.c_str()))return prop.m_Offset;
	}
	if (table.childs.size() > 0)
	{
		for (const m_table& t : table.childs)
		{
			return get_offset_g(m_offset, t);
		}
	}
	return 0;
}

*/
