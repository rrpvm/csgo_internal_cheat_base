#include "sdk.hpp"
#include "../hooks/vgui_panel_hook.h"
#include "../hooks/chclient_hook.hpp"
#include "../model_render_hook.hpp"
#include "client_class.hpp"//delete this
#include "../render_view_hook.hpp"
#include "../client_mode_hook.hpp"
#include "../convars_hook.hpp"
#include "../hooks/MinHook/MinHook.h"
bool sdk::initialize()
{
	Interfaces::debug_overlay = reinterpret_cast<c_debug_overlay*>(create_interface("engine.dll", VDEBUG_OVERLAY_INTERFACE_VERSION));
	Interfaces::client_entity_list = reinterpret_cast<c_client_entity_list*>(create_interface("client.dll", VCLIENTENTITYLIST_INTERFACE_VERSION));
	Interfaces::vgui_panel = reinterpret_cast<i_panel*>(create_interface("vgui2.dll", VGUI_PANEL_INTERFACE_VERSION));
	Interfaces::i_client_engine = reinterpret_cast<i_engine_client*>(create_interface("engine.dll", VENGINE_CLIENT_INTERFACE_VERSION));
	Interfaces::base_client_dll = reinterpret_cast<i_base_client_dll*>(create_interface("client.dll", CLIENT_DLL_INTERFACE_VERSION));
	Interfaces::g_surface = reinterpret_cast<i_surface*>(create_interface("vguimatsurface.dll", "VGUI_Surface031"));
	Interfaces::g_mdl_render = reinterpret_cast<i_model_render*>(create_interface("engine.dll", VENGINE_HUDMODEL_INTERFACE_VERSION));
	Interfaces::g_mat_system = reinterpret_cast<i_material_system*>(create_interface("materialsystem.dll", MATERIAL_SYSTEM_INTERFACE_VERSION));
	Interfaces::g_event_manager = reinterpret_cast<i_game_event_manager*>(create_interface("engine.dll", INTERFACEVERSION_GAMEEVENTSMANAGER2));
	Interfaces::g_fx_client = reinterpret_cast<i_effects*>(create_interface("client.dll", IEFFECTS_INTERFACE_VERSION));
	Interfaces::g_cvar = reinterpret_cast<icvar*>(create_interface("vstdlib.dll", CVAR_INTERFACE_VERSION));
	Interfaces::g_trace = reinterpret_cast<i_engine_trace*>(create_interface("engine.dll", IENGINEINTERFACE));
	Interfaces::g_model_info = reinterpret_cast<i_model_info*>(create_interface("engine.dll", "VModelInfoClient004"));


	Interfaces::g_device  = **reinterpret_cast<IDirect3DDevice9***>(utils.pattern_scan("shaderapidx9.dll", (BYTE*)("\xA1\x00\x00\x00\x00\x50\x8B\x10"), "x????xxx")+0x1);
	Interfaces::g_input = *reinterpret_cast<c_input**>(utils.pattern_scan("client.dll", (BYTE*)("\xA1\x00\x00\x00\x00\x51\xF3\x0F\x11\x04\x24"), "x????xxxxxx")+0x1);
	Interfaces::global_vars = **reinterpret_cast<c_global_vars***>(utils.pattern_scan("client.dll", (BYTE*)("\xA1\x00\x00\x00\x00\x56\xF3\x0F\x10\x40\x00"), "x????xxxxx?")+0x1);
	do {
		Interfaces::g_client_mode = **(i_client_mode***)((*(uintptr_t**)Interfaces::base_client_dll)[10] + 0x5);
		/*	
		HudProcessInput+3 ::                    mov     ecx, G_ClientModee
		ecx = +0x4; G_ClientMode = +0x5		
		*/
	} while (!Interfaces::g_client_mode);

	//Interfaces::g_render_view = **reinterpret_cast<i_render_view***>(utils.pattern_scan("client.dll", (BYTE*)("\x8B\x06\x8B\xCE\xFF\x50\x20\x5F\x5E"), "xxxxxxxxx")+0x1);
	//Interfaces::g_render_view = *(i_render_view**)(utils.PatternScan(GetModuleHandle("client.dll"), "A1 ? ? ? ? B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? FF 10") + 1);
	assert(Interfaces::g_device);
	assert(Interfaces::g_input);
	assert(Interfaces::global_vars);
	assert(Interfaces::g_client_mode);
//	assert(Interfaces::g_render_view);

	
	
	

	



	return (Interfaces::debug_overlay && Interfaces::client_entity_list
	&& Interfaces::vgui_panel && Interfaces::i_client_engine && Interfaces::base_client_dll && Interfaces::g_surface
	&& Interfaces::g_mdl_render && Interfaces::g_mat_system && Interfaces::g_event_manager && Interfaces::g_fx_client
	&& Interfaces::g_cvar && Interfaces::g_trace && Interfaces::g_model_info
	);
}
bool sdk::hook()
{
	this->dump_offsets();
	MH_Initialize();
	vgui_panel_hook::getInstance().init();
	chclient_hook::getInstance().init();
	model_render_hook::getInstance().init();
	render_view_hook::getInstance().init();
	client_mode_hook::getInstance().init();
	convars_hook::getInstance().init();	
	MH_EnableHook(MH_ALL_HOOKS);
	Interfaces::g_event_manager->add_listener(&c_event_manager, "player_hurt", false);
	Interfaces::g_event_manager->add_listener(&c_event_manager, "bullet_impact", false);
	convar* cam_thrp_pitch = Interfaces::g_cvar->find_var("cam_idealpitch");
	convar* cam_thrp_yaw = Interfaces::g_cvar->find_var("cam_idealyaw");
	if (cam_thrp_pitch && cam_thrp_yaw)
	{
		cam_thrp_pitch->set_int(0);
		cam_thrp_yaw->set_int(0);
	}
	return true;
}
void sdk::unhook()
{
	Interfaces::g_event_manager->remove_listener(&c_event_manager);
	vgui_panel_hook::getInstance().unhook();
	chclient_hook::getInstance().unhook();
	model_render_hook::getInstance().unhook();
	render_view_hook::getInstance().unhook();
	client_mode_hook::getInstance().unhook();
	convars_hook::getInstance().unhook();
}
void sdk::dump_offsets()
{
	ClientClass* allClasses = Interfaces::base_client_dll->get_all_classes();
	netvar_manager::getInstance().dump_table(allClasses);
}
