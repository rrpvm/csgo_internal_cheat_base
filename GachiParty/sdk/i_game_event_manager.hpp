#pragma once
#include "i_game_event_listener.hpp"
#include "IGameEvent.hpp"
#define INTERFACEVERSION_GAMEEVENTSMANAGER2	"GAMEEVENTSMANAGER002"
class i_base_interface
{
public:
	virtual	~i_base_interface() {}
};
class i_game_event_manager : public i_base_interface
{
public:
	virtual	~i_game_event_manager(void) {};
	// load game event descriptions from a file eg "resource\gameevents.res"
	virtual int load_events_from_file(const char* filename) = 0;
	// removes all and anything
	virtual void  reset() = 0;
	// adds a listener for a particular event
	virtual bool add_listener(i_game_event_listener* listener, const char* name, bool bServerSide) = 0;
	// returns true if this listener is listens to given event
	virtual bool find_listener(i_game_event_listener* listener, const char* name) = 0;
	// removes a listener 
	virtual void remove_listener(i_game_event_listener* listener) = 0;
	// add a listener that listens to all events. 
	virtual bool add_listener_global(i_game_event_listener* listener, bool bServerSide) = 0;
	// create an event by name, but doesn't fire it. returns NULL is event is not
	// known or no listener is registered for it. bForce forces the creation even if no listener is active
	virtual i_game_event* create_event(const char* name, bool bForce = false, int* pCookie = NULL) = 0;
	// fires a server event created earlier, if bDontBroadcast is set, event is not send to clients
	virtual bool fire_event(i_game_event* event, bool bDontBroadcast = false) = 0;
	// fires an event for the local client only, should be used only by client code
	virtual bool fire_event_client_side(i_game_event* event) = 0;
	// create a new copy of this event, must be free later
	virtual i_game_event* duplicate_event(i_game_event* event) = 0;
	// if an event was created but not fired for some reason, it has to bee freed, same UnserializeEvent
	virtual void free_event(i_game_event* event) = 0;
	// write/read event to/from bitbuffer
	virtual bool serialize_event(i_game_event* event, void* eventMsg) = 0;
	virtual i_game_event* unserialize_event(const void*& eventMsg) = 0; // create new KeyValues, must be deleted
};
