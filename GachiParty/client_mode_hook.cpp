#include "client_mode_hook.hpp"
#include "sdk/sdk.hpp"
#include "sdk/c_view_setup.hpp"
#include "data_base.hpp"
typedef void(__thiscall* o_override_view)(void* , c_view_setup* );
typedef bool(__thiscall* o_should_draw_crosshair)(void* );

void __fastcall	hkOverrideView(void* ecx, int edx, c_view_setup* pSetup)
{
	static const auto original = client_mode_hook::getInstance().getVMT().getOriginalFunction<o_override_view>(18);
	if(!data_base::getInstance().get_local_player())return original(Interfaces::g_client_mode, pSetup);
	pSetup->fov = 100.0f;
	static bool on = true;
	
	if (!Interfaces::g_input->m_fCameraInThirdPerson && on)//fixme
	{
		Interfaces::g_input->m_fCameraInThirdPerson = true;
		Interfaces::g_input->m_vecCameraOffset.z = 190.0f;
	}
	else if(!on)Interfaces::g_input->m_fCameraInThirdPerson = false;
	if (GetAsyncKeyState(VK_F1)&1)on = !on;
	original(Interfaces::g_client_mode, pSetup);
}
bool __fastcall	should_draw_crosshair(void* ecx, int edx)
{
 	static const auto original = client_mode_hook::getInstance().getVMT().getOriginalFunction<o_should_draw_crosshair>(28);
	bool should = original(Interfaces::g_client_mode);
	return data_base::getInstance().get_local_player() ? true : should;
}

void client_mode_hook::init()
{
	this->getVMT().init(Interfaces::g_client_mode);
	this->getVMT().hookAt(18, hkOverrideView);
	//this->getVMT().hookAt(28, should_draw_crosshair);
	this->getVMT().join();
}
