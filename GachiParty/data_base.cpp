#include "data_base.hpp"
#include "sdk/sdk.hpp"
void data_base::update_player_list()
{
	this->data_players.clear();
	this->local_player = nullptr;
	if (!Interfaces::i_client_engine->is_in_game_connected())return;
	if (Interfaces::client_entity_list->get_client_entity(Interfaces::i_client_engine->get_local_player()) != nullptr)
	{
		this->local_player = reinterpret_cast<c_base_entity*>(Interfaces::client_entity_list->get_client_entity(Interfaces::i_client_engine->get_local_player()));
	}
	else {
		return;
	}
	int local_team = this->local_player->team();
	for (short i = 1; i < Interfaces::i_client_engine->get_max_client(); ++i)
	{
		i_client_entity* entity = Interfaces::client_entity_list->get_client_entity(i);
		if (!entity)continue;
		c_base_entity* ent = reinterpret_cast<c_base_entity*>(entity);
		if (!ent)continue;
		const auto get_player_data = [&, this](c_base_entity* ent) {
			c_player_data data;
			data.entity = ent;
			data.hp = ent->hp();
			data.b_dormant = ent->is_dormant();
			data.is_enemy = local_team != ent->team();
			data.pos =ent->position();
			data.i = i;
			player_info_t t;
			Interfaces::i_client_engine->get_player_info(i, &t);
			data.name = std::string(t.szName);
			this->get_data_players().emplace_back(data);
		};
		get_player_data(ent);
	}
}
