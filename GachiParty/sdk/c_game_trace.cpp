#include "c_game_trace.hpp"
#include "c_base_entity.hpp"

int c_game_trace::get_entity_index() const {
	if (entity)return entity->entindex();
	return -1;
}