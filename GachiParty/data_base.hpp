#pragma once
#include "sdk/c_base_entity.hpp"
#include <vector>
#include <string>
#include "sdk/vector.h"
#include "Singleton.h"
#define cPlayerDataInvalidationNumber -1337
struct c_player_data {
	c_base_entity* entity;
	int i;
	int hp;
	bool b_dormant;
	bool is_enemy;
	Vector pos;	
	std::string name;	
	c_player_data() {  i = -1; hp = 0; b_dormant = true; is_enemy = false; pos = Vector(0, 0, 0); entity = nullptr; };
	c_player_data(const c_player_data& v)
	{
		this->entity = v.entity;
		this->hp = v.hp;
		this->i = v.i;
		this->name = v.name;
		this->b_dormant = v.b_dormant;
		this->is_enemy = v.is_enemy;
		this->pos = v.pos;
	}
	c_player_data operator=(const c_player_data& v)
	{
		if (this == &v)return *this;
		this->entity = v.entity;
		this->hp = v.hp;
		this->i = v.i;
		this->name = v.name;
		this->b_dormant = v.b_dormant;
		this->is_enemy = v.is_enemy;
		this->pos = v.pos;
		return *this;
	}
};
class data_base: public Singleton<data_base> {
public:
	data_base() {
		data_players = std::vector<c_player_data>(64);
	};
	~data_base() {};
	void update_player_list();
	std::vector<c_player_data>& get_data_players() { return data_players; };
	c_base_entity* get_local_player() { return local_player; };

private:
	std::vector<c_player_data>data_players;
	c_base_entity* local_player;
};