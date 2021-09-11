#pragma once
#include <deque>
#include "sdk/i_game_event_manager.hpp"
#include "../GachiParty/sdk/vector.h"
class event_manager : public i_game_event_listener {
private:
	struct hit_data_str {
		hit_data_str() {
			curr_time = 0.0f;
			hitbox_pos = Vector(0, 0, 0);
			damage = 0;
			entity_id = -1;
		}
		float curr_time;
		Vector hitbox_pos;
		int damage;
		int entity_id;
	};
	std::deque<hit_data_str>hit_data;//should use hit_data_str or use pointer to hit_data_str? /*hit_data_str* hit_data */
public:
	virtual	~event_manager(void) {};
	virtual void fire_game_event(i_game_event* event) override;
	virtual int	 get_event_debug_id(void) {
		return EVENT_DEBUG_ID_INIT;
	}
	void on_paint();
	
private:
	void post_event_bullet_impact(const i_game_event* _event);
	void post_event_player_hurt(const i_game_event* _event);
	std::deque<std::pair<Vector,float>>local_player_bullets_position;//store last bullets last 1.5seconds
	const float save_data_time_max = 1.50f;
	//Vector local_player_last_bullet_position;
};
inline event_manager c_event_manager;