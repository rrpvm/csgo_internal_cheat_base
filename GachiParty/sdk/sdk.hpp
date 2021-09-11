#pragma once
#include "../utils.hpp"
#include "../hooks/vmt.hpp"
#include "../includes/win_modules.hpp"
#include "debug_overlay.hpp"
#include "client_entity_list.hpp"
#include "i_panel.hpp"
#include "i_client_engine.h"
#include "i_base_client_dll.hpp"
#include "i_surface.hpp"
#include "c_global_vars.hpp"
#include "c_input.hpp"
#include "i_model_render.hpp"
#include "i_material_system.hpp"
#include "i_effects.hpp"
#include "c_base_entity.hpp"
#include "i_render_view.hpp"
#include "i_client_mode.hpp"
#include "icvar.hpp"
#include "i_engine_trace.hpp"
#include <d3d9.h>
#include "i_game_event_manager.hpp"
#include "i_model_info.hpp"

#include "../event_manager.hpp"
#include <intrin.h>
typedef void* (__cdecl* fn_create_interface)(const char* i_name, int return_code);
class sdk {
public:
	sdk()  {};
	bool initialize();
	bool hook();
	void unhook();
	static void* create_interface(const std::string& dll_name,const std::string& inteface_name) {
		HMODULE dll = GetModuleHandle(dll_name.c_str());
		if (!dll)return nullptr;
		fn_create_interface function = (fn_create_interface)GetProcAddress(dll, "CreateInterface");
		if (!function)return nullptr;
		return function(inteface_name.c_str(), 0);
	}
	void dump_offsets();
};
namespace Interfaces {
	inline IDirect3DDevice9* g_device = nullptr;
	//valve interfaces
	inline c_global_vars* global_vars = nullptr;
	inline i_base_client_dll* base_client_dll = nullptr;
	inline i_engine_client* i_client_engine = nullptr;
	inline c_client_entity_list* client_entity_list = nullptr;
	inline i_surface* g_surface = nullptr;
	inline i_panel* vgui_panel = nullptr;
	inline c_debug_overlay* debug_overlay = nullptr;
	inline c_input* g_input = nullptr;
	inline i_model_render* g_mdl_render = nullptr;
	inline i_material_system* g_mat_system = nullptr;
	inline i_game_event_manager* g_event_manager = nullptr;
	inline i_effects* g_fx_client = nullptr;
	inline i_render_view* g_render_view = nullptr;
	inline i_client_mode* g_client_mode = nullptr;
	inline icvar* g_cvar = nullptr;
	inline i_engine_trace* g_trace = nullptr;
	inline i_model_info* g_model_info = nullptr;
}
inline std::unique_ptr<sdk>c_sdk(new sdk());
/*
indexes:
CHCLient:
CreateMove - 22
FrameStageNotify - 22 + 14 + nullsub = 37
DME - 21
*/
/*

"\xA1\x00\x00\x00\x00\x50\x8B\x10", "x????xxx" + 0x1 -> d3d9device
"\xA1\x00\x00\x00\x00\x51\xF3\x0F\x11\x04\x24", "x????xxxxxx" + 0x1 -> C_Input
"\xA1\x00\x00\x00\x00\x56\xF3\x0F\x10\x40\x00"), "x????xxxxx?" + 0x1 - > global vars

*/