#pragma once
#include "client_renderable.hpp"
#define VENGINE_HUDMODEL_INTERFACE_VERSION	"VEngineModel016"
typedef unsigned short ModelInstanceHandle_t;

struct studiohdr_t;//can be deleted
class i_material;//can be deleted
struct studiohwdata_t;//can be deleted
typedef int StudioDecalHandle_t;//can be deleted
class IMatRenderContext;//can be deleted
enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SELECTIVE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};
struct DrawModelState_t
{
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	i_client_renderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	StudioDecalHandle_t		m_decals;
	int						m_drawFlags;
	int						m_lod;
};
struct ModelRenderInfo_t
{
	Vector origin;//0x0
	QAngle angles;//0xC
	bool pad[4];//0x18
	i_client_renderable* pRenderable;//0x1C
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
};
class i_model_render
{
public:
	virtual int		draw_model(int flags,
								i_client_renderable * pRenderable,
								ModelInstanceHandle_t instance,
								int entity_index,
								const model_t * model,
								Vector const& origin,
								QAngle const& angles,
								int skin,
								int body,
								int hitboxset,
								const matrix3x4_t * modelToWorld = NULL,
								const matrix3x4_t * pLightingOffset = NULL) = 0;

	virtual void	forced_material_override(i_material* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL, int nMaterialIndex = -1) = 0;
	virtual bool	is_forced_material_override() = 0;
	virtual void	set_view_target(const void* pStudioHdr, int nBodyIndex, const Vector& target) = 0;
	virtual ModelInstanceHandle_t create_instance(i_client_renderable* pRenderable, void* pCache = NULL) = 0;
	virtual void destroy_instance(ModelInstanceHandle_t handle) = 0;
	virtual void set_static_lighting(ModelInstanceHandle_t handle, void* pHandle) = 0;
	virtual void get_static_lighting(ModelInstanceHandle_t handle) = 0;
	virtual bool change_instance(ModelInstanceHandle_t handle, i_client_renderable* pRenderable) = 0;
	virtual void add_decal(ModelInstanceHandle_t handle, void* const& ray,Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = 0, i_material* pSpecifyMaterial = NULL, float w = 1.0f, float h = 1.0f, void* pvProxyUserData = NULL, int nAdditionalDecalFlags = 0) = 0;
	virtual void remove_all_decals(ModelInstanceHandle_t handle) = 0;
	virtual bool model_has_decals(ModelInstanceHandle_t handle) = 0;
	virtual void remove_all_decals_from_all_models(bool bRenderContextValid) = 0;
	virtual void* draw_model_shadow_setup(i_client_renderable* pRenderable, int body, int skin, void* pInfo, void* pCustomBoneToWorld = NULL) = 0;
	virtual void draw_model_shadow(i_client_renderable* pRenderable, const void*& info, void* pCustomBoneToWorld = NULL) = 0;
	virtual bool recompute_static_lighting(ModelInstanceHandle_t handle) = 0;
	virtual void release_all_static_prop_color_data(void) = 0;
	virtual void restore_all_static_prop_color_data(void) = 0;
	virtual int	draw_model_ex(ModelRenderInfo_t& pInfo) = 0;
	virtual int	draw_model_static_ex_prop(IMatRenderContext* pRenderContext, ModelRenderInfo_t& pInfo) = 0;
	virtual bool draw_model_setup(IMatRenderContext* pRenderContext, ModelRenderInfo_t& pInfo, DrawModelState_t* pState, matrix3x4_t** ppBoneToWorldOut) = 0;
	virtual void draw_model_execute(IMatRenderContext* pRenderContext, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL) = 0;
	virtual void setup_lighting(const Vector& vecCenter) = 0;
	virtual int DrawStaticPropArrayFast(void* pProps, int count, bool bShadowDepth) = 0;
	virtual void SuppressEngineLighting(bool bSuppress) = 0;
	virtual void SetupColorMeshes(int nTotalVerts) = 0;
	virtual void SetupLightingEx(const Vector& vecCenter, ModelInstanceHandle_t handle) = 0;
	virtual bool GetBrightestShadowingLightSource(const Vector& vecCenter, Vector& lightPos, Vector& lightBrightness, bool bAllowNonTaggedLights) = 0;
	virtual void ComputeLightingState(int nCount, const void* pQuery, void* pState, void** ppEnvCubemapTexture) = 0;
	virtual void GetModelDecalHandles(void* pDecals, int nDecalStride, int nCount, const ModelInstanceHandle_t* pHandles) = 0;
	virtual void ComputeStaticLightingState(int nCount, const void* pQuery, void* pState, void* pDecalState, void** ppStaticLighting, void** ppEnvCubemapTexture, void* pColorMeshHandles) = 0;
	virtual void CleanupStaticLightingState(int nCount, void* pColorMeshHandles) = 0;
};
