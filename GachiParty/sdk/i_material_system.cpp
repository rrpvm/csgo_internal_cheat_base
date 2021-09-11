#include "i_material_system.hpp"
#include "../hooks/vmt_l.hpp"
inline i_material* i_material_system::create_material(const char* pMaterialName, KeyValues* pVMTKeyValues)
{
    return vmt_load::call_function<83, i_material*>(this, pMaterialName, pVMTKeyValues);
}

 i_material* i_material_system::find_material(char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
{
    return vmt_load::call_function<84, i_material*>(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}

inline MaterialHandle_t i_material_system::first_material()
{
    return vmt_load::call_function<85, MaterialHandle_t>(this);
}

inline MaterialHandle_t i_material_system::next_material(MaterialHandle_t h)
{
    return vmt_load::call_function<86, MaterialHandle_t>(this, h);
}

inline MaterialHandle_t i_material_system::invalid_material()
{
    return vmt_load::call_function<87, MaterialHandle_t>(this);
}

inline i_material* i_material_system::get_material(MaterialHandle_t h)
{
    return vmt_load::call_function<88, i_material*>(this, h);
}
