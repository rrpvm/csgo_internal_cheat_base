#include "vgui_panel_hook.h"
#include "../sdk/sdk.hpp"
#include "../data_base.hpp"
#include "../esp.h"
typedef void(__thiscall* orig_function)(void* ecx, VPANEL, bool, bool);
void __fastcall hook_paint_traverse(void* ecx, int edx, VPANEL vguiPanel, bool forceRepaint, bool allowForce = true)
{

	static orig_function original_paint_traverse = vgui_panel_hook::getInstance().getVMT().getOriginalFunction<orig_function>(41);
	original_paint_traverse(ecx, vguiPanel, forceRepaint, allowForce);
	const char* name = Interfaces::vgui_panel->get_name(vguiPanel);
	static int panel_id = 0;
	if (panel_id == 0 && !strcmp(name, "FocusOverlayPanel"))panel_id = vguiPanel;
	if (vguiPanel != panel_id)return;
	for (c_player_data& entity : data_base::getInstance().get_data_players())
	{
		if (!entity.entity || entity.entity == data_base::getInstance().get_local_player()|| entity.b_dormant)continue;
		if(entity.is_enemy)esp->box_esp(entity);
	}
	c_event_manager.on_paint();
}
void vgui_panel_hook::init()
{
	this->getVMT().init(Interfaces::vgui_panel);
	this->getVMT().hookAt(41, hook_paint_traverse);
	this->getVMT().join();
}
