#pragma once
#include "Singleton.h"
#include "hooks/base_hook_class.hpp"
#include "hooks/MinHook.h"
class convar;
class convars_hook : public Singleton<convars_hook>, public i_base_hook {
public:
	virtual ~convars_hook() {};
	convar* weapon_spread_show{ nullptr };
	convar* sv_cheats{ nullptr };
	MinHook wpn_debug_spread_hook;
	MinHook sv_cheats_hook;
	void init() override;
};