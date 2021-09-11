#pragma once
class c_base_entity;
class c_base_player;
class c_view_setup;
class c_user_cmd;
class i_client_mode
{
	// Misc.
public:

	virtual			~i_client_mode() {}
	virtual void	init_viewport() = 0;
	// One time init when .dll is first loaded.
	virtual void	iInit() = 0;
	// Called when vgui is shutting down.
	virtual void	vgui_shutdown() = 0;
	// One time call when dll is shutting down
	virtual void	shutdown() = 0;
	// Called when switching from one IClientMode to another.
	// This can re-layout the view and such.
	// Note that Enable and Disable are called when the DLL initializes and shuts down.
	virtual void	enable() = 0;
	virtual void	enable_with_root_panel(unsigned int pRoot) = 0;
	// Called when it's about to go into another client mode.
	virtual void	disable() = 0;
	virtual void	lLayout(bool bForce = false) = 0;
	// Gets at the viewport, if there is one...
	virtual void* get_viewport() = 0;
	// Gets a panel hierarchically below the viewport by name like so "ASWHudInventoryMode/SuitAbilityPanel/ItemPanel1"...
	virtual void* get_panel_from_viewport(const char* pchNamePath) = 0;
	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual void* get_viewport_animation_controller() = 0;
	// called every time shared client dll/engine data gets changed,
	// and gives the cdll a chance to modify the data.
	virtual void	process_input(bool bActive) = 0;
	// The mode can choose to draw/not draw entities.
	virtual bool	should_draw_details_objects() = 0;
	virtual bool	should_draw_entitity(c_base_entity* pEnt) = 0;
	virtual bool	should_draw_local_player(c_base_player* pPlayer) = 0;
	virtual bool	should_draw_particles() = 0;
	// The mode can choose to not draw fog
	virtual bool	shoukd_Draw_fog(void) = 0;
	virtual void	override_view(c_view_setup* pSetup) = 0;
	virtual void	override_audio_state(void* pAudioState) = 0;
	virtual int		key_input(int down, unsigned int keynum, const char* pszCurrentBinding) = 0;//20
	virtual void	start_message_mode(int iMessageModeType) = 0;
	virtual void* get_message_panel() = 0;
	virtual void	override_mouse_input(float* x, float* y) = 0;
	virtual bool	create_move(float flInputSampleTime, c_user_cmd* cmd) = 0;

	virtual void	level_init(const char* newmap) = 0;
	virtual void	level_shutdown(void) = 0;
	// Certain modes hide the view model
	virtual bool	should_draw_viewmodel(void) = 0;
	virtual bool	should_draw_crosshair(void) = 0;//28
	// Let mode override viewport for engine
	virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height) = 0;
	// Called before rendering a view.
	virtual void	PreRender(c_view_setup* pSetup) = 0;
	// Called after everything is rendered.
	virtual void	PostRender(void) = 0;
	virtual void	PostRenderVGui() = 0;
	virtual void	ActivateInGameVGuiContext(void* pPanel) = 0;
	virtual void	DeactivateInGameVGuiContext() = 0;
	virtual float	get_viewmodel_fov(void) = 0;
	virtual bool	CanRecordDemo(char* errorMsg, int length) const = 0;
	virtual wchar_t* GetServerName(void) = 0;
	virtual void		SetServerName(wchar_t* name) = 0;
	virtual wchar_t* GetMapName(void) = 0;
	virtual void		SetMapName(wchar_t* name) = 0;
	virtual void	OnColorCorrectionWeightsReset(void) = 0;
	virtual float	GetColorCorrectionScale(void) const = 0;
	virtual int		HudElementKeyInput(int down, unsigned int keynum, const char* pszCurrentBinding) = 0;
	virtual void	DoPostScreenSpaceEffects(const c_view_setup* pSetup) = 0;
	virtual void	UpdateCameraManUIState(int iType, int nOptionalParam, unsigned __int64 xuid) = 0;
	virtual void	ScoreboardOff(void) = 0;
	virtual void	GraphPageChanged(void) = 0;
	// Updates.
public:

	// Called every frame.
	virtual void	Update() = 0;

	virtual void	SetBlurFade(float scale) = 0;
	virtual float	GetBlurFade(void) = 0;
};