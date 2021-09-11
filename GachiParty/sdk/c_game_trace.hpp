#pragma once
#include <cstddef>
#include "vector.h"
class c_base_entity;
class i_client_entity;
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)
#define DISPSURF_FLAG_SURFPROP3		(1<<5)
#define DISPSURF_FLAG_SURFPROP4		(1<<6)
struct cplane_t
{
	Vector	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];
};
class c_base_trace
{
public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }
	bool IsDispSurfaceProp3(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP3) != 0); }
	bool IsDispSurfaceProp4(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP4) != 0); }
public:
	// these members are aligned!!
	Vector			startpos;				// start position
	Vector			endpos;					// final position
	cplane_t		plane;					// surface normal at impact
	float			fraction;				// time completed, 1.0 = didn't hit anything
	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data
	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area
	c_base_trace() {}
};
struct csurface_t
{
	const char* name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

class c_game_trace : public c_base_trace
{
public:
	bool did_hit_world() const;
	bool did_hit_non_world_entity() const;
	int get_entity_index() const;
	bool did_hit() const;
	bool visible();
public:
	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	csurface_t		surface;			// surface hit (impact surface)
	int				hitgroup;			// 0 == generic, non-zero is specific body part
	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable
	i_client_entity* entity;
	int			hitbox;					// box hit by trace in studio
	c_game_trace() : entity(NULL) {}
};
inline bool c_game_trace::did_hit_world() const
{
	return false;
}
inline bool c_game_trace::did_hit_non_world_entity() const
{
	return false;
}

inline bool c_game_trace::did_hit() const
{
	return fraction < 1 || allsolid || startsolid;
}
inline bool c_game_trace::visible()
{
	if (entity && fraction > 0.97f)return true;
	return false;
}
typedef c_game_trace trace_t;