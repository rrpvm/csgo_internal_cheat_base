#pragma once
#include "convar.hpp"
#include "i_app_system.hpp"

#define CVAR_INTERFACE_VERSION "VEngineCvar007"
class icvar : public IAppSystem
{
public:

	virtual void* skip00() = 0;
	virtual void			reginster_con_command(con_command_base* pCommandBase) = 0;
	virtual void			unreginster_con_command(con_command_base* pCommandBase) = 0;
	virtual void			unreginster_con_commands(void* id) = 0;
	virtual const char* get_command_line_value(const char* pVariableName) = 0;
	virtual con_command_base* find_command_base(const char* name) = 0;
	virtual const con_command_base* find_command_base(const char* name) const = 0;
	virtual convar* find_var(const char* var_name) = 0;
	virtual const convar* find_var(const char* var_name) const = 0;//8
	virtual void* find_command(const char* name) = 0;
	virtual const void* find_command(const char* name) const = 0;
	virtual void			install_global_change_callbacks(FnChangeCallback_t callback) = 0;//11
	virtual void			remove_global_change_callbacks(FnChangeCallback_t callback) = 0;
	virtual void			call_global_change_callbacks(convar* var, const char* pOldString, float flOldValue) = 0;
	virtual void			InstallConsoleDisplayFunc(void* pDisplayFunc) = 0;//14
	virtual void			RemoveConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void			console_color_printf(const void*& clr,  const char* pFormat, ...)  = 0;
	virtual void			console_printf(const char* pFormat, ...) = 0;//17
	virtual void			console_d_printf(const char* pFormat, ...) = 0;
	virtual void			revert_flagged_convar(int nFlag) = 0;//19
	//virtual void			InstallCVarQuery(ICvarQuery* pQuery) = 0;
	virtual void			pSip20() = 0;
	virtual void			SetMaxSplitScreenSlots(int nSlots) = 0;
	virtual int				GetMaxSplitScreenSlots() const = 0;
	virtual void			AddSplitScreenConVars() = 0;
	virtual void			RemoveSplitScreenConVars(void* id) = 0;
	virtual int				GetConsoleDisplayFuncCount() const = 0;
	virtual void			GetConsoleText(int nDisplayFuncIndex, char* pchText, size_t bufSize) const = 0;
	virtual bool			IsMaterialThreadSetAllowed() const = 0;
	virtual void			QueueMaterialThreadSetValue(convar* pConVar, const char* pValue) = 0;
	virtual void			QueueMaterialThreadSetValue(convar* pConVar, int nValue) = 0;
	virtual void			QueueMaterialThreadSetValue(convar* pConVar, float flValue) = 0;
	virtual bool			HasQueuedMaterialThreadConVarSets() const = 0;
	virtual int				ProcessQueuedMaterialThreadConVarSets() = 0;
protected:
	virtual void* FactoryInternalIterator(void) = 0;
};
