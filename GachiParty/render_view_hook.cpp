#include "render_view_hook.hpp"
#include "sdk/sdk.hpp"
#include "sdk/c_view_setup.hpp"
typedef void(__thiscall* o_render_view)(void*ecx,const c_view_setup&, const c_view_setup&, int nClearFlags, int whatToDraw);
void __stdcall 	hkRenderView(const  c_view_setup& view, const c_view_setup& hudViewSetup, int nClearFlags, int whatToDraw)
{
	static const auto original = render_view_hook::getInstance().getVMT().getOriginalFunction<o_render_view>(6);
	//view.fov = 120.0f;
	original(Interfaces::g_render_view, view, hudViewSetup, nClearFlags, whatToDraw);
}
void render_view_hook::init()
{
	/*this->getVMT().init(Interfaces::g_render_view);
	this->getVMT().hookAt(6, hkRenderView);
	this->getVMT().join();*/
}
