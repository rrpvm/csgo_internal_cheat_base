#pragma once
#include <memory>
#include <string>
#include "sdk/vector.h"
#include "sdk/c_base_entity.hpp"
#include "data_base.hpp"
class c_esp {
public:
	c_esp() {
		
	};
	void box_esp(const c_player_data& data);


};

inline std::unique_ptr<c_esp>esp(new c_esp());