#pragma once
#include "client_unknown.hpp"
class i_client_thinkable
{
public:
	// Gets at the containing class...
	virtual i_client_unknown* get_i_client_unknown() = 0;
	virtual void				client_think() = 0;
	virtual void*	get_think_handle() = 0;
	virtual void				set_think_handle(void* hThink) = 0;
	// Called by the client when it deletes the entity.
	virtual void				release() = 0;
};
