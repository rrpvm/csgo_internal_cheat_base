#pragma once
#include "Singleton.h"
#include "hooks/base_hook_class.hpp"
class client_mode_hook : public Singleton<client_mode_hook>, public i_base_hook {
public:
	virtual ~client_mode_hook() {};
	void init() override;
};