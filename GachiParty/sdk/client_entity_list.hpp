#pragma once
#include "client_networkable.hpp"
#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"
class c_client_entity_list
{
public:
	virtual c_client_networkable* get_client_networkable(int entnum) = 0;
	virtual c_client_networkable* get_client_networkable_from_handle(c_base_handle hEnt) = 0;
	virtual i_client_unknown* get_client_unkown_from_handle(c_base_handle hEnt) = 0;
	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->Geti_client_entity().
	virtual i_client_entity* get_client_entity(int entnum) = 0;
	virtual i_client_entity* get_client_entity_from_handle(c_base_handle hEnt) = 0;
	virtual int					numbers_of_entities(bool bIncludeNonNetworkable) = 0;
	virtual int					get_highest_entity_index(void) = 0;
	virtual void				set_max_entities(int maxents) = 0;
	virtual int					get_max_entities() = 0;
};