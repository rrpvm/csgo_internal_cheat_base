#include "chclient_hook.hpp"
#include "../sdk/sdk.hpp"
#include "../data_base.hpp"
#include "../c_legitbot.hpp"

typedef void(__thiscall* o_frame_stage_notify)(void* ecx,ClientFrameStage_t);
typedef void(__thiscall* o_create_move)(void* ecx,  int , float , bool );
void __stdcall hkFrameStageNotify(ClientFrameStage_t frame_stage)
{
	static o_frame_stage_notify original = chclient_hook::getInstance().getVMT().getOriginalFunction<o_frame_stage_notify>(37);
	original(Interfaces::base_client_dll, frame_stage);
	if (frame_stage == FRAME_RENDER_START)
	{
		
		data_base::getInstance().update_player_list();
	}
}
void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	static o_create_move original = chclient_hook::getInstance().getVMT().getOriginalFunction<o_create_move>(22);
	original(Interfaces::base_client_dll, sequence_number, input_sample_frametime, active);
	c_user_cmd* cmd = Interfaces::g_input->get_user_cmd(sequence_number);
	c_verified_user_cmd* cmd_f = Interfaces::g_input->get_verified_cmd(sequence_number);
	if (!cmd ||!cmd->command_number || !Interfaces::i_client_engine->is_in_game_connected())return;	
	auto local_player = data_base::getInstance().get_local_player();
	if (!local_player)return;

	g_legitbot->bunnyhope(cmd, local_player);
	if(cmd->buttons & IN_ATTACK)g_legitbot->aimbot(cmd, local_player, data_base::getInstance().get_data_players());

	//DEBUG
	if(local_player->hp() > 0)
	Interfaces::i_client_engine->set_view_angels(&cmd->viewangles);


	cmd_f->m_cmd = *cmd;
	cmd_f->m_crc = cmd->GetChecksum();
	
}
/*__declspec(naked) void __fastcall hkCreateMove_Proxy(void* _this, int, int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		push ebp
		mov  ebp, esp
		push ebx; not sure if we need this
		push esp
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call hkCreateMove
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}*/
void chclient_hook::init()
{
	this->getVMT().init(Interfaces::base_client_dll);
	this->getVMT().hookAt(37, hkFrameStageNotify);
	this->getVMT().hookAt(22, hkCreateMove);
	this->getVMT().join();
}
