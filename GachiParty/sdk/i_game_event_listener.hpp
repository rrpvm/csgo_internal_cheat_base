#pragma once
class i_game_event;
class i_game_event_listener//2
{
public:
	virtual	~i_game_event_listener(void) {};
	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void fire_game_event(i_game_event* event) = 0;
	virtual int	 get_event_debug_id(void) = 0;
};