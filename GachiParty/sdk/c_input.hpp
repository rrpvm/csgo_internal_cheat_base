#pragma once
#include "c_user_cmd.h"
#include "../hooks/vmt_l.hpp"
#define MAX_SPLITSCREEN_PLAYERS 1
class Vector;
class c_input {
public:
	char                pad_0x00[0x0C];
	bool                m_trackir_available;
	bool                m_mouse_initiated;
	bool                m_mouse_active;
	bool                m_fJoystickAdvancedInit;
	char                pad_0x08[0x2C];
	void* m_pKeys;
	char                pad_0x38[0x6C];
	bool                m_fCameraInterceptingMouse;
	bool                m_fCameraInThirdPerson;
	bool                m_fCameraMovingWithMouse;
	Vector		    m_vecCameraOffset;
	bool                m_fCameraDistanceMove;
	int                 m_nCameraOldX;
	int                 m_nCameraOldY;
	int                 m_nCameraX;
	int                 m_nCameraY;
	bool                m_CameraIsOrthographic;
	Vector              m_angPreviousViewAngles;
	Vector              m_angPreviousViewAnglesTilt;
	float               m_flLastForwardMove;
	int                 m_nClearInputState;
	char                pad_0xE4[0x8];
	c_user_cmd* m_pCommands;
	c_verified_user_cmd* m_pVerifiedCommands;

	c_user_cmd* get_user_cmd(int sequence_number)
	{
		return vmt_load::call_function<8, c_user_cmd*>((void*)this,0, sequence_number);//CInput::GetUserCmd(int nSlot, int sequence_number)
	};
	c_verified_user_cmd* get_verified_cmd(int sequence_number)
	{
		 c_verified_user_cmd* cmds = *(c_verified_user_cmd**)((uintptr_t)this + 0xF8);
		 return &cmds[sequence_number % MULTIPLAYER_BACKUP];
	}
	//CAM_THINK 31
};
/*class CInput
{
public:
	char pad_0000[179]; //0x0000
	bool N000000E7; //0x00B3
	bool thirdPerson; //0x00B4
	bool camera_moving_mouse; //0x00B5
	Vector3 N00000142; //0x00B6
	bool f_camera_distance_move; //0x00C2
	int32_t N000000EC; //0x00C3
	int32_t N00000131; //0x00C7
	int32_t N00000135; //0x00CB
	int32_t N00000136; //0x00CF
	bool camera_is_orto; //0x00D3
	Vector3 ang_prev; //0x00D4
	Vector3 ang_prev_tilt; //0x00E0
	float last_f_move; //0x00EC
	int32_t clear_input_state; //0x00F0
	void* p_commands; //0x00F4
	void* pVerified; //0x00F8
	char pad_00FC[76]; //0x00FC
}; //Size: 0x0148*/