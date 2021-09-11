#pragma once
class c_global_vars {
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			absoluteframestarttimestddev;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				simTicksThisFrame;
	int				network_protocol;
};