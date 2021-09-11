#pragma once
#include <vector>
#include <memory>
#include <optional>
class c_base_entity;//del
class c_user_cmd;//del
struct c_player_data;//del
//#include "sdk/c_user_cmd.h"
//#include "data_base.hpp"
#define PI 3.14159265359
#define RAD  57.2957795131
#define RAD_TO_DEG(x)x*=RAD
#define DEG_TORAD(x)x/=RAD
enum aimTargetPriorityList{
	byDistance = 0,
	byHealthPoints,
	byCrosshair,
	byDamage//semirage
};
class c_legitbot {
public:
	c_legitbot() { curr_aim_prority = byDistance; };
	void bunnyhope(c_user_cmd* cmd,  c_base_entity* local_player);
	void aimbot(c_user_cmd* cmd,  c_base_entity* local_player, const std::vector<c_player_data>& data);
private:
	std::optional<c_player_data> get_best_aim_target(int priority, c_base_entity* local_player, const std::vector<c_player_data>& data);
	int curr_aim_prority = byDistance;
};
inline std::unique_ptr<c_legitbot>g_legitbot(new c_legitbot());