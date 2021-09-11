#pragma once
class VPlane;
class ITexture;
class c_base_entity;
class c_view_setup;
class i_material;
struct  vrect_t;
#define I_CLIENT_RENDER_VIEW_INTERFACE "VEngineRenderView014"
class i_render_view
{
public:
	virtual void		init(void) = 0;
	virtual void		level_init(void) = 0;
	virtual void		level_shutdown(void) = 0;
	virtual void		shutdown(void) = 0;
	virtual void		on_render_start() = 0;
	virtual	void		render(vrect_t* rect) = 0;
	virtual void		render_view(const c_view_setup& view, const c_view_setup& hudViewSetup, int nClearFlags, int whatToDraw) = 0;
	virtual int get_draw_flags() = 0;
	virtual void		start_pitch_drift(void) = 0;
	virtual void		stop_pitch_drift(void) = 0;
	virtual VPlane* get_frustum() = 0;
	virtual bool		should_draw_brush_models(void) = 0;
	virtual const c_view_setup* get_player_view_setup(int nSlot = -1) const = 0;
	virtual const c_view_setup* get_view_setup(void) const = 0;
	virtual void		disable_vis(void) = 0;
	virtual int			BuildWorldListsNumber() const = 0;
	virtual void		SetCheapWaterStartDistance(float flCheapWaterStartDistance) = 0;
	virtual void		SetCheapWaterEndDistance(float flCheapWaterEndDistance) = 0;
	virtual void		GetWaterLODParams(float& flCheapWaterStartDistance, float& flCheapWaterEndDistance) = 0;
	virtual void		drift_pitch(void) = 0;
	virtual void		SetScreenOverlayMaterial(i_material* pMaterial) = 0;
	virtual i_material* GetScreenOverlayMaterial() = 0;
	virtual void		WriteSaveGameScreenshot(const char* pFilename) = 0;
	virtual void		WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height) = 0;
	// Draws another rendering over the top of the screen
	virtual void		QueueOverlayRenderView(const c_view_setup& view, int nClearFlags, int whatToDraw) = 0;
	// Returns znear and zfar
	virtual float		GetZNear() = 0;
	virtual float		GetZFar() = 0;
	// Returns the min/max fade distances, and distance scale
	virtual void		GetScreenFadeDistances(float* pMin, float* pMax, float* pScale) = 0;
	virtual c_base_entity* GetCurrentlyDrawingEntity() = 0;
	virtual void		SetCurrentlyDrawingEntity(c_base_entity* pEnt) = 0;
	virtual bool		UpdateShadowDepthTexture(ITexture* pRenderTarget, ITexture* pDepthTexture, const c_view_setup& shadowView, bool bRenderWorldAndObjects = true, bool bRenderViewModels = false) = 0;
	virtual void		FreezeFrame(float flFreezeTime) = 0;
	virtual void		InitFadeData(void) = 0;
};