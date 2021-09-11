#pragma once
#include "iconvar.hpp"
class con_command_base;
typedef con_command_base baseclass;
class con_command_base {
public:

	virtual						~con_command_base(void) = 0;
	virtual	bool				is_command(void)  = 0;
	virtual bool				is_flag_set(int flag)  = 0;
	virtual void				add_flags(int flags) = 0;
	virtual void				remvoe_flags(int flags) = 0;
	virtual int					get_flags() const = 0;
	virtual const char* get_name(void) const = 0;
	virtual const char* get_help_text(void) const = 0;
	virtual bool				is_registered(void)  = 0;
	// Returns the DLL identifier
	virtual void* get_dll_identifier() const = 0;
	virtual void				create(const char* pName, const char* pHelpString = 0,
		int flags = 0) = 0;
	// Used internally by OneTimeInit to initialize/shutdown
	virtual void				init() = 0;
};
class convar : public con_command_base, public iconvar
{
public:
	__int32 get_int()
	{
		return vmt_load::call_function<13, __int32>(this);
	}
	float get_float()
	{
		return vmt_load::call_function<12, float>(this);
	}
	void set_int(int value)
	{
		return vmt_load::call_function<16, void>(this,value);
	}
	void set_float(float value)
	{
		return vmt_load::call_function<15, void>(this, value);
	}
	struct CVValue_t
	{
		char* m_pszString;
		int							m_StringLength;

		// Values
		float						m_fValue;
		int							m_nValue;
	};
private:
	virtual void				internal_set_value(const char* value) = 0;;
	virtual void				internal_set_float_value(float fNewValue) = 0;;
	virtual void				internal_set_int_value(int nValue) = 0;;
	virtual void				internal_set_color_value(void* value) = 0;;
	virtual bool				clamp_value(float& value) = 0;;
	virtual void				change_string_value(const char* tempVal, float flOldValue) = 0;;
	virtual void				create(const char* pName, const char* pDefaultValue, int flags = 0,
		const char* pHelpString = 0, bool bMin = false, float fMin = 0.0,
		bool bMax = false, float fMax = false, FnChangeCallback_t callback = 0) = 0;;
	// Used internally by OneTimeInit to initialize.
	virtual void				Init() = 0;;

protected:
	convar* m_pParent;
	// Static data
	const char* m_pszDefaultValue;
	CVValue_t					m_Value;
	// Min/Max values
	bool						m_bHasMin;
	float						m_fMinVal;
	bool						m_bHasMax;
	float						m_fMaxVal;
	// Call this function when ConVar changes
	//CUtlVector< FnChangeCallback_t > m_fnChangeCallbacks;
};