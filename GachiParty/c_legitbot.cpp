#include "c_legitbot.hpp"
#include "sdk/c_user_cmd.h"
#include "data_base.hpp"
#include "sdk/sdk.hpp"
void c_legitbot::bunnyhope(c_user_cmd* cmd, c_base_entity* local_player)
{
	uintptr_t dwFlags = local_player->flags();
	if (dwFlags & FL_INWATER || dwFlags & FL_FROZEN)return;
	/*super-puper bunny hope*/
	if (cmd->buttons & IN_JUMP && !(dwFlags & FL_ONGROUND))
	{
		cmd->buttons &= ~IN_JUMP;
	}
	if (dwFlags == FL_ONGROUND && !(cmd->buttons & IN_JUMP))
	{
		cmd->buttons |= IN_JUMP;
	}
}

void c_legitbot::aimbot(c_user_cmd* cmd, c_base_entity* local_player, const std::vector<c_player_data>& data)
{
	auto best_target = get_best_aim_target(this->curr_aim_prority, local_player, data);
	if (!best_target.has_value())return;
	auto target = best_target.value();
	Vector local_eye_pos = local_player->position() + local_player->get_view_offset();
	Vector enemy_head = target.entity->get_hitbox_pos(0);//delete this(hitbox 0)
	Vector difference = enemy_head - local_eye_pos;
	float yaw = atan2f(difference.y, difference.x);
	RAD_TO_DEG(yaw);
	float pitch = -asinf(difference.z / difference.Length());
	RAD_TO_DEG(pitch);
	cmd->viewangles.pitch = pitch;
	cmd->viewangles.yaw = yaw;
	cmd->viewangles -= QAngle(local_player->aim_punch_angle() * 2.0f);//move to rcs
	cmd->viewangles.nrml();
}

std::optional<c_player_data> c_legitbot::get_best_aim_target(int priority, c_base_entity* local_player, const std::vector<c_player_data>& data)
{
	static bool only_visible = true;
	static int hitbox = 0;
	if (!local_player)return std::nullopt;
	const auto get_by_dst = [](int priority, c_base_entity* local_player, const std::vector<c_player_data>& data) {
		float max = FLT_MAX;
		int target_index = 65;//invalid
		for (const c_player_data& entity : data)
		{
			if (entity.b_dormant || !entity.is_enemy || entity.hp <= 0 || entity.entity == local_player)continue;	
			if (only_visible && !local_player->visible(entity.entity, hitbox))	continue;
			float dst = entity.pos.DistTo(local_player->position());
			if (dst <= max)
			{
				max = dst;
				target_index = entity.i - 1;
			}
		}
		return target_index == 65? std::nullopt: std::optional<c_player_data>(data.at(target_index));
	};
	if (priority == byDistance)return get_by_dst(priority, local_player, data);
	return std::nullopt;
}
