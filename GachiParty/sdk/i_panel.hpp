#pragma once
#define VGUI_PANEL_INTERFACE_VERSION "VGUI_Panel009"
#include "../hooks/vmt_l.hpp"
typedef unsigned int VPANEL;
class i_panel {
public:
	void paint_traverse(VPANEL vguiPanel, bool forceRepaint, bool allowForce = true)
	{
		vmt_load::call_function<41, void>((void*)this, vguiPanel, forceRepaint, allowForce);
	}
	const char* get_name(VPANEL vguiPanel)
	{
		return vmt_load::call_function<36, const char*>((void*)this, vguiPanel);
	}	
};