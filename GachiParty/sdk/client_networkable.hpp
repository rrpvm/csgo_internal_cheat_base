#pragma once
#include "client_unknown.hpp"
class ClientClass;
enum ShouldTransmitState_t
{
	SHOULDTRANSMIT_START = 0,	// The entity is starting to be transmitted (maybe it entered the PVS).
	SHOULDTRANSMIT_END		// Called when the entity isn't being transmitted by the server.
};
enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,	// indicates it was created +and+ entered the pvs
DATA_UPDATE_DATATABLE_CHANGED,
};
typedef void* bf_read;//delete this
class c_client_networkable
{
public:
	virtual i_client_unknown* get_i_client_unknown() = 0;
	virtual void			release() = 0;
	virtual ClientClass* get_client_class() = 0;
	virtual void			notify_should_transmit(ShouldTransmitState_t state) = 0;
	virtual void			on_pre_data_changed(DataUpdateType_t updateType) = 0;
	virtual void			on_data_changed(DataUpdateType_t updateType) = 0;
	virtual void			pre_data_update(DataUpdateType_t updateType) = 0;
	virtual void			post_data_update(DataUpdateType_t updateType) = 0;
	virtual void			OnDataUnchangedInPVS() = 0;//csgp leak
	virtual bool			is_dormant(void) = 0;
	virtual int				entindex(void) const = 0;
	virtual void			recieve_message(int classID, bf_read& msg) = 0;
	virtual void* get_data_table_base_ptr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
};