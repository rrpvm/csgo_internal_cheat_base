#pragma once
#include <cstdint>

class vmt_load {
public:
	template <int index, typename ret_type, typename ... args_>
	static __forceinline ret_type call_function(void* base, args_... args)
	{
		typedef ret_type(__thiscall* virtual_function)(void* ecx,args_...);
		uintptr_t* vftable = *(uintptr_t**)(base);
		virtual_function function = (virtual_function)(vftable[index]);
		return function(base, args...);
	}
private:
};