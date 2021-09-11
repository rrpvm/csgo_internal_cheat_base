#include "convars_hook.hpp"
#include "sdk/sdk.hpp"
typedef int(__thiscall* o_get_int)(void* );
int __fastcall hkGetInt(void* ecx, int edx)
{
	const static auto dwDrawCrosshairAdr = reinterpret_cast<uintptr_t*>(utils.pattern_scan("client.dll", (PBYTE)"\x85\xC0\x0F\x84\xF3\x04", "xxxxxx"));//test eax eax (10653e60)
	const uintptr_t* dwAddress = reinterpret_cast<uintptr_t*>(_ReturnAddress());
	const static o_get_int original = convars_hook::getInstance().wpn_debug_spread_hook.get_manual_orig<o_get_int, 13>();
	if(!dwDrawCrosshairAdr)return original(ecx);	
	if (*dwAddress == *dwDrawCrosshairAdr)
	{
		if (dwAddress == dwDrawCrosshairAdr)return 1;
		else  return original(ecx);
	}
	else return original(ecx);
}
int __fastcall hkGetInt_svcheats(void* ecx, int edx)
{
	const static auto oCamThink = reinterpret_cast<uintptr_t*>(utils.pattern_scan("client.dll", (PBYTE)"\x85\xC0\x75\x30\x38\x86", "xxxxxx"));//.text:102DF4BF                 test    eax, eax ; .text:102DF4C1                 jnz     short loc_102DF4F3
	const uintptr_t* dwAddress = reinterpret_cast<uintptr_t*>(_ReturnAddress());
	const static o_get_int original = convars_hook::getInstance().sv_cheats_hook.get_manual_orig<o_get_int, 13>();
	if (!oCamThink)return original(ecx);
	if (*dwAddress == *oCamThink)
	{
		if (dwAddress == oCamThink)return 1;
		else  return original(ecx);
	}
	else return original(ecx);
}
void convars_hook::init()
{
	this->weapon_spread_show = Interfaces::g_cvar->find_var("weapon_debug_spread_show");
	this->sv_cheats = Interfaces::g_cvar->find_var("sv_cheats");
	if (!this->weapon_spread_show || !this->sv_cheats)return;
	wpn_debug_spread_hook.init(this->weapon_spread_show);
	wpn_debug_spread_hook.hookAt(13, hkGetInt);

	sv_cheats_hook.init(this->sv_cheats);
	sv_cheats_hook.hookAt(13, hkGetInt_svcheats);
}
