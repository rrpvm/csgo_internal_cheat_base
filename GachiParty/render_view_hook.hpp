#pragma once
#include "Singleton.h"
#include "hooks/base_hook_class.hpp"
class render_view_hook : public Singleton<render_view_hook>, public i_base_hook {
public:
	virtual ~render_view_hook() {};
	void init() override;
private:
};