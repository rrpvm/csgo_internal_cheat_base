#pragma once
#include "../Singleton.h"
#include "base_hook_class.hpp"
class vgui_panel_hook : public Singleton<vgui_panel_hook>, public i_base_hook{
public:
	virtual ~vgui_panel_hook() {};
	void init() override;
};