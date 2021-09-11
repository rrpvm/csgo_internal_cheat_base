#pragma once
#include "../Singleton.h"
#include "base_hook_class.hpp"
class chclient_hook : public Singleton<chclient_hook>, public i_base_hook {
public:
	virtual ~chclient_hook() {};
	void init() override;
private:
};