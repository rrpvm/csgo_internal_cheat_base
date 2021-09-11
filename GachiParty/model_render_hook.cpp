#include "model_render_hook.hpp"
#include "sdk/sdk.hpp"

typedef void(__fastcall* fnDrawModelExecute)(void*, int, IMatRenderContext*, const DrawModelState_t&, ModelRenderInfo_t&, matrix3x4_t*);
void __fastcall hk_draw_model_execute(void* _this, int edx,IMatRenderContext* pRenderContext, const DrawModelState_t& state,  ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL)
{
	static fnDrawModelExecute original = model_render_hook::getInstance().getVMT().getOriginalFunction<fnDrawModelExecute>(21);
	static i_material* mat = Interfaces::g_mat_system->find_material("debug/debugambientcube");
	if(!Interfaces::i_client_engine->is_in_game_connected() || Interfaces::g_mdl_render->is_forced_material_override())return original(_this, edx, pRenderContext, state, pInfo, pCustomBoneToWorld);
	//if(pInfo.entity_index > 64 || pInfo.entity_index < 0)return original(_this, edx, pRenderContext, state, pInfo, pCustomBoneToWorld);	
	const char* model_name = pInfo.pModel->szName;
	bool shadow = strstr(model_name, "models/player/contactshadow") != nullptr;
	bool is_arm = strstr(model_name, "arms") != nullptr;
	bool is_player = strstr(model_name, "models/player") != nullptr;
	bool is_weapon = strstr(model_name, "models/weapon") != nullptr;
	bool is_sleeve = strstr(model_name, "sleeve") != nullptr;
	if (is_player && !shadow)
	{
		mat->set_material_var_flag(MATERIAL_VAR_IGNOREZ, true);
		Interfaces::g_mdl_render->forced_material_override(mat);
	}
	original(_this, edx, pRenderContext, state, pInfo, pCustomBoneToWorld);
	Interfaces::g_mdl_render->forced_material_override(nullptr);
}

void model_render_hook::init()
{
	this->getVMT().init(Interfaces::g_mdl_render);
	this->getVMT().hookAt(21, hk_draw_model_execute);
	this->getVMT().join();

}
