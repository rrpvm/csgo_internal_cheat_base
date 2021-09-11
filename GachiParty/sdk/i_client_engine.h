#pragma once
#include "../sdk/vector.h"
#include "../hooks/vmt_l.hpp"
#define VENGINE_CLIENT_INTERFACE_VERSION		"VEngineClient014"
enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};
typedef struct player_info_s
{
	__int64 unknown;

	union
	{
		__int64 steamID64;

		struct
		{
			__int32 xuid_low;
			__int32 xuid_high;
		};
	};

	char            szName[128];
	int             userId;
	char            szSteamID[20];
	char            pad_0x00A8[0x10];
	unsigned long   iSteamID;
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customfiles[4];
	unsigned char   filesdownloaded;
} player_info_t;
class i_engine_client {
public:
	void get_screen_size(int& width, int& height)
	{
		vmt_load::call_function<5, void>((void*)(this), width, height);
	}
	bool get_player_info(int ent_num, player_info_t* pinfo) {
		return vmt_load::call_function<8, bool>((void*)this, ent_num, pinfo);
	}
	int get_player_for_userid(int uid)
	{
		return vmt_load::call_function<9, int>((void*)this, uid);
	}
	int get_local_player(void)
	{
		return vmt_load::call_function<12, int>((void*)(this));
	}
	void get_view_angels(QAngle* view_angels)
	{
		vmt_load::call_function<18, void>((void*)(this), view_angels);
	}
	void set_view_angels(QAngle* view_angels)
	{
		vmt_load::call_function<19, void>((void*)(this), view_angels);
	}
	int get_max_client()
	{
		return vmt_load::call_function<20, int>((void*)(this));
	}
	bool is_in_game()
	{
		return vmt_load::call_function<26, bool>((void*)(this));
	}
	bool is_connected()
	{
		return vmt_load::call_function<27, bool>((void*)(this));
	}
	bool is_in_game_connected() {
		return is_in_game() && is_connected();
	}
	void execure_client_cmd(const char* szCmdString)
	{
		vmt_load::call_function<108, void>((void*)(this), szCmdString);
	}
	void client_cmd_unrestricted(const char* szCmdString)//update this shit
	{
		vmt_load::call_function<114, void>((void*)(this), szCmdString);
	}
};
