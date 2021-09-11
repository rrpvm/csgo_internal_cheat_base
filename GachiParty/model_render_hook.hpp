#pragma once
#include "Singleton.h"
#include "hooks/base_hook_class.hpp"
class model_render_hook : public Singleton<model_render_hook>, public i_base_hook {
public:
	virtual ~model_render_hook() {};
	void init() override;
};