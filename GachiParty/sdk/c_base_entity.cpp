//#include "c_base_entity.hpp"
#include "sdk.hpp"
#include "netvars.hpp"
#include "matrix.hpp"
#include "../data_base.hpp"

int c_base_entity::hp()
{
    static uintptr_t offset = netvar_manager::getInstance().get_offset("DT_BasePlayer", "m_iHealth");
    return *(uintptr_t*)(reinterpret_cast<uintptr_t>(this) + offset);
}
int c_base_entity::team()
{
    static uintptr_t offset = netvar_manager::getInstance().get_offset("DT_BaseEntity", "m_iTeamNum");
    return *(int*)(reinterpret_cast<uintptr_t>(this) + offset);
}
uintptr_t c_base_entity::flags()
{
    static uintptr_t offset = netvar_manager::getInstance().get_offset("DT_BasePlayer", "m_fFlags");
    return *(uintptr_t*)(reinterpret_cast<uintptr_t>(this) + offset);
}
Vector c_base_entity::position()
{
    static uintptr_t offset = netvar_manager::getInstance().get_offset("DT_BaseEntity", "m_vecOrigin");
    return *(Vector*)(reinterpret_cast<uintptr_t>(this) + offset);
}
Vector c_base_entity::get_bone_pos(int bone_id)
{
    matrix3x4_t matrix[128];
    if (this->SetupBones(matrix, 128, BONE_USED_BY_ANYTHING, 0.0f))
    {
        float x = matrix[bone_id][0][3];
        float y = matrix[bone_id][1][3];
        float z = matrix[bone_id][2][3];
        return Vector(x, y, z);
    }
    return Vector{};
}
Vector c_base_entity::get_hitbox_pos(int hitbox_id)
{
    matrix3x4_t boneMatrix[MAXSTUDIOBONES];

    if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
        auto studio_model = Interfaces::g_model_info->GetStudiomodel(GetModel());
        if (studio_model) {
            auto hitbox = studio_model->GetHitboxSet(0)->GetHitbox(hitbox_id);
            if (hitbox) {
                auto min = Vector{},max = Vector{};

                Utilities::vec_transform(hitbox->bbmin, boneMatrix[hitbox->bone], min);
                Utilities::vec_transform(hitbox->bbmax, boneMatrix[hitbox->bone], max);

                return (min + max) / 2.0f;
            }
        }
    }
    return Vector{};
}
Vector c_base_entity::get_view_offset()
{
    static uintptr_t offset  = netvar_manager::getInstance().get_offset("DT_BasePlayer","DT_LocalPlayerExclusive", "m_vecViewOffset[0]");
   return *(Vector*)(reinterpret_cast<uintptr_t>(this) + offset);
   // return *(Vector*)(reinterpret_cast<uintptr_t>(this) + 0x108);
}
Vector c_base_entity::aim_punch_angle()
{
    static uintptr_t offset = netvar_manager::getInstance().get_offset_g(274,"m_aimPunchAngle");/*DT_LOCAL*/
    return *(Vector*)(reinterpret_cast<uintptr_t>(this) + offset);
}
bool c_base_entity::visible(c_base_entity* entity, int hitbox)
{
    auto local_player = data_base::getInstance().get_local_player();
    if (!local_player || !entity)return false;
    Vector local_eye_pos = local_player->position() + local_player->get_view_offset();
    Vector enemy_head = entity->get_hitbox_pos(hitbox);//get hitbox instead of get_bone_pos
    Ray_t ray; ray.Init(local_eye_pos, enemy_head);
    trace_t trace; c_trace_filter filter;
    filter.skip = local_player;
    Interfaces::g_trace->trace_ray(ray, CONTENTS_HITBOX | CONTENTS_SOLID | CONTENTS_GRATE, &filter, &trace);
    return trace.visible();
}

