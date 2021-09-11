#include "esp.h"
#include "sdk/sdk.hpp"




void c_esp::box_esp(const c_player_data& data)
{
	
	if (data.is_enemy)
	{
		if (data.hp <= 0)return;
		Vector head2d;
		Vector pos2d;
		Interfaces::debug_overlay->screen_position(data.entity->get_bone_pos(8) + Vector(0,0,10), head2d);
		Interfaces::debug_overlay->screen_position(data.pos, pos2d);
		int h = pos2d.y - head2d.y;
		int w = h / 2.5;
		Interfaces::g_surface->draw_set_color(0, 255, 0, 255);
		Interfaces::g_surface->draw_outlined_rect(head2d.x - w, head2d.y, head2d.x + w, pos2d.y);
	}
	else {

	}
}


