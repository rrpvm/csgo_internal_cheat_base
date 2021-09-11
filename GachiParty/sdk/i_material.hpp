#pragma once
#include "vector.h"
typedef void KeyValues;//delete this
typedef void IMaterialVar;//delete this

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_PSEUDO_TRANSLUCENT = (1 << 9), // used to mark water materials for rendering after opaques but before translucents (with alpha blending but also with depth writes)
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
	MATERIAL_VAR_AOPREPASS = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_MULTIPLY = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),

	// NOTE: Only add flags here that either should be read from
	// .vmts or can be set directly from client code. Other, internal
	// flags should to into the flag enum in IMaterialInternal.h
};
class i_material
{
public:
	virtual const char* get_name() const = 0;
	virtual const char* get_texture_group_name() const = 0;
	virtual void* pSkip02(int* width, int* height,void* imageFormat, bool* isTranslucent) const = 0;
	virtual void* pSkip03(unsigned char* data,int width, int height,void* imageFormat) const = 0;
	virtual int				get_mapping_width() = 0;
	virtual int				get_mapping_heigth() = 0;
	virtual int				get_animation_frames() = 0;
	virtual bool			in_material_page(void) = 0;
	virtual	void			get_material_offset(float* pOffset) = 0;
	virtual void			get_material_scale(float* pScale) = 0;
	virtual i_material* get_material_page(void) = 0;
	virtual IMaterialVar* find_var(const char* varName, bool* found, bool complain = true) = 0;
	virtual void			incriment_reference_count(void) = 0;
	virtual void			decrement_reference_count(void) = 0;
	inline void add_ref() { incriment_reference_count(); }
	inline void release() { decrement_reference_count(); }
	virtual int 			get_enumaration_id(void) const = 0;
	virtual void			get_low_res_color_sample(float s, float t, float* color) const = 0;
	virtual void			pSkip000() = 0;
	virtual bool			is_translucent() = 0;
	virtual bool			is_alpha_tested() = 0;
	virtual bool			is_vertex_lit() = 0;
	virtual /*vertex_format_t*/int	GetVertexFormat() const = 0;
	virtual bool			has_proxy(void) const = 0;
	virtual bool			uses_env_cubemap(void) = 0;
	virtual bool			pSkip004(void) = 0;
	virtual bool			pSkip001(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			pSkip002(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			pSkip003(void) = 0;
	// Apply constant color or alpha modulation
	virtual void			alpha_modulate(float alpha) = 0;
	virtual void			color_modulate(float r, float g, float b) = 0;
	// Material Var flags...
	virtual void			set_material_var_flag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool			get_material_var_flag(MaterialVarFlags_t flag) const = 0;
	virtual void			get_reflectivity(Vector& reflect) = 0;
	virtual bool			GetPropertyFlag(void* type) = 0;
	virtual bool			is_two_sided() = 0;
	virtual void			set_shder(const char* pShaderName) = 0;
	virtual int				get_num_passes(void) = 0;
	virtual int				get_texture_memory_bytes(void) = 0;
	virtual void			refresh() = 0;
	// GR - returns true is material uses lightmap alpha for blending
	virtual bool			pSKip005(void) = 0;
	virtual bool			pSkip006(void) = 0;
	virtual int				shader_param_count() const = 0;
	virtual IMaterialVar** get_shader_params(void) = 0;
	virtual bool			is_error_material() const = 0;
	virtual void			unused() {}
	virtual float			get_alpha_modulation() = 0;
	virtual void			get_color_modulation(float* r, float* g, float* b) = 0;
	virtual bool			IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;
	virtual IMaterialVar* FindVarFast(char const* pVarName, unsigned int* pToken) = 0;
	virtual void			SetShaderAndParams(KeyValues* pKeyValues) = 0;//KeyValues*
	virtual const char* get_shader_name() const = 0;
	virtual void			DeleteIfUnreferenced() = 0;
	virtual bool			IsSpriteCard() = 0;
	virtual void			CallBindProxy(void* proxyData, void* pCallQueue) = 0;
	virtual void			RefreshPreservingMaterialVars() = 0;
	virtual bool			WasReloadedFromWhitelist() = 0;
	virtual bool			SetTempExcluded(bool bSet, int nExcludedDimensionLimit = 0) = 0;
	virtual int				get_reference_count() const = 0;
};
