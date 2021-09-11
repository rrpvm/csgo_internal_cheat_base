#pragma once
#include "client_unknown.hpp"
#include "client_networkable.hpp"
#include "client_renderable.hpp"
#include "i_client_thinkable.hpp"
class i_client_entity : public i_client_unknown, public i_client_renderable, public c_client_networkable, public i_client_thinkable
{
public:
	// Delete yourself.
	virtual void			release(void) = 0;
	// Network origin + angles
	virtual const Vector& get_abs_origin(void) const = 0;//ÍÅ ÈÑÏÎËÜÇÎÂÀÒÜ
	virtual const QAngle& get_abs_angels(void) const = 0;//ÍÅ ÈÑÏÎËÜÇÎÂÀÒÜ
	virtual void* get_mouth(void) = 0;
	virtual bool			get_sound_specialization(void* info) = 0;
};
