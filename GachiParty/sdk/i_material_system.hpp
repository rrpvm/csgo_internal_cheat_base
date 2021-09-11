#pragma once
#include "i_app_system.hpp"
#include "i_material.hpp"
#define MATERIAL_SYSTEM_INTERFACE_VERSION		"VMaterialSystem080"
typedef unsigned short MaterialHandle_t;
class i_material_system: public IAppSystem {
public:
	inline i_material* create_material(const char* pMaterialName, KeyValues* pVMTKeyValues);//83
	 i_material* find_material(char const* pMaterialName, const char* pTextureGroupName = nullptr, bool complain = true, const char* pComplainPrefix = NULL);//84
	inline MaterialHandle_t	first_material();//85
	inline MaterialHandle_t	next_material(MaterialHandle_t h);//86
	inline MaterialHandle_t	invalid_material();//87
	inline i_material* get_material(MaterialHandle_t h);//88
};