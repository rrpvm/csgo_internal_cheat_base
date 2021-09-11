#include "event_manager.hpp"
#include <string.h>
#include "sdk/sdk.hpp"
#include "data_base.hpp"
void event_manager::fire_game_event(i_game_event* _event)
{
	if (!data_base::getInstance().get_local_player())return;
	if (!strcmp(_event->get_name(), "bullet_impact"))post_event_bullet_impact(_event);
	if (!strcmp(_event->get_name(), "player_hurt"))post_event_player_hurt(_event);
	

}
void event_manager::on_paint()
{
	const auto clear = [&]() {
		//if (!this->local_player_bullets_position.empty())
		//{
			while (!this->local_player_bullets_position.empty()&& Interfaces::global_vars->curtime - this->local_player_bullets_position.front().second > save_data_time_max)this->local_player_bullets_position.pop_front();
		//}
		//if(!this->hit_data.empty())
			while (!this->hit_data.empty() && Interfaces::global_vars->curtime - this->hit_data.front().curr_time > save_data_time_max)this->hit_data.pop_front();	
	};	
	clear();
	 c_base_entity* c_local_player = data_base::getInstance().get_local_player();
	if (!c_local_player)return;
	for (auto data : this->hit_data)
	{
		Interfaces::debug_overlay->add_line_overlay(c_local_player->get_view_offset() + c_local_player->position(), data.hitbox_pos, 255, 0, 0, true, 0.4f);
	}
}
void event_manager::post_event_bullet_impact(const i_game_event* _event)
{
	i_client_entity* ent = Interfaces::client_entity_list->get_client_entity(Interfaces::i_client_engine->get_player_for_userid(_event->get_int("userid")));
	if (!ent || ent != data_base::getInstance().get_local_player())return;
	this->local_player_bullets_position.push_back({ Vector(_event->get_float("X"), _event->get_float("Y"), _event->get_float("Z")), Interfaces::global_vars->curtime });
}
void event_manager::post_event_player_hurt(const i_game_event* _event)
{
	i_client_entity* ent = Interfaces::client_entity_list->get_client_entity(Interfaces::i_client_engine->get_player_for_userid(_event->get_int("userid")));
	i_client_entity* attacker = Interfaces::client_entity_list->get_client_entity(Interfaces::i_client_engine->get_player_for_userid(_event->get_int("attacker")));
	if (!ent || !attacker || this->local_player_bullets_position.empty())return;
	c_base_entity* player = reinterpret_cast<c_base_entity*>(ent);
	c_base_entity* attacker_ent = reinterpret_cast<c_base_entity*>(attacker);
	if (player == attacker_ent || attacker_ent != data_base::getInstance().get_local_player())return;
	hit_data_str hit_data_s;
	hit_data_s.curr_time = Interfaces::global_vars->curtime;
	hit_data_s.damage = _event->get_int("dmg_health");
	hit_data_s.entity_id = player->entindex();
	Vector* heap_vect = new Vector(attacker_ent->get_view_offset() + attacker_ent->position());
	Interfaces::debug_overlay->add_line_overlay(*heap_vect, this->local_player_bullets_position.front().first, 255, 0, 0, true, 0.4f);
	Ray_t ray; ray.Init(*heap_vect, this->local_player_bullets_position.front().first);
	trace_t trace; c_trace_filter filter;
	filter.skip = attacker;
	Interfaces::g_trace->trace_ray(ray, CONTENTS_HITBOX | CONTENTS_SOLID | CONTENTS_GRATE, &filter, &trace);
	//const auto trace = utils.trace_ray_utl(attacker_ent,  this->local_player_bullets_position.front().first, *heap_vect, CONTENTS_HITBOX);
	if (trace.entity)
	{
		const auto pos = player->get_hitbox_pos(trace.hitbox);
		hit_data_s.hitbox_pos = pos;
		this->hit_data.emplace_back(hit_data_s);
	}
	delete heap_vect;
	heap_vect = nullptr;
	ZeroMemory(&hit_data_s, sizeof(hit_data_str));

}
