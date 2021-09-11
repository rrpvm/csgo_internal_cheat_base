#pragma once
#include "vector.h"
#include "c_game_trace.hpp"
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};
class i_handle_entity;
class i_collidable;
struct matrix3x4_t;
#define	CONTENTS_EMPTY			0		// No contents
#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE
#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))
#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	
#define CONTENTS_BLOCKLIGHT		0x400
#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_AREAPORTAL		0x8000
#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
#define	CONTENTS_BRUSH_PAINT	0x40000
#define	CONTENTS_GRENADECLIP	0x80000
#define	CONTENTS_UNUSED2		0x100000
#define	CONTENTS_UNUSED3		0x200000
#define	CONTENTS_UNUSED4		0x400000
#define	CONTENTS_UNUSED5		0x800000
#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity
#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)// water physics in these contents
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)// for csgo weapon clipping
#define MASK_WEAPONCLIPPING			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS)// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)// hits solids (not grates) and passes through everything else
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)// everything normally solid, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)// everything normally solid for player movement, except monsters (world+brush only)
class i_trace_filter
{
public:
	virtual bool should_hit_entity(i_handle_entity * pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};
class c_trace_filter : i_trace_filter {
public:
	bool should_hit_entity(i_handle_entity* pEntityHandle, int /*contentsMask*/)
	{
		return !(pEntityHandle == skip);
	}
	virtual TraceType_t GetTraceType() const
	{
		return TraceType_t::TRACE_EVERYTHING;
	}
	void* skip{ nullptr };
};
struct Ray_t
{
	VectorAligned  m_Start;	// starting point, centered within the extents
	VectorAligned  m_Delta;	// direction + length of the ray
	VectorAligned  m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;	// Describes an axis aligned box extruded along a ray
	const matrix3x4_t* m_pWorldAxisTransform;
	bool	m_IsRay;	// are the extents zero?
	bool	m_IsSwept;	// is delta != 0?

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector const& start, Vector const& end)
	{
		m_Delta = end - start;		

		m_IsSwept = (m_Delta.LengthSqr() != 0);
		VectorClear(m_Extents);
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;
		// Offset m_Start to be in the center of the box...
		VectorClear(m_StartOffset);
		VectorCopy(start, m_Start);
	}

	/*void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		Assert(&end);
		VectorSubtract(end, start, m_Delta);

		m_pWorldAxisTransform = NULL;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		VectorSubtract(maxs, mins, m_Extents);
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		Assert(m_Extents.x >= 0 && m_Extents.y >= 0 && m_Extents.z >= 0);
		// Offset m_Start to be in the center of the box...
		VectorAdd(mins, maxs, m_StartOffset);
		m_StartOffset *= 0.5f;
		VectorAdd(start, m_StartOffset, m_Start);
		m_StartOffset *= -1.0f;
	}
	*/
	// compute inverse delta
	Vector InvDelta() const
	{
		Vector vecInvDelta;
		for (int iAxis = 0; iAxis < 3; ++iAxis)
		{
			if (m_Delta[iAxis] != 0.0f)
			{
				vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
			}
			else
			{
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}

private:
};

class i_engine_trace
{
public:
	virtual int		get_point_contents(const Vector& vecAbsPosition, int contentsMask = MASK_ALL, i_handle_entity** ppEntity = NULL) = 0;
	virtual int		get_points_contents_world_only(const Vector& vecAbsPosition, int contentsMask = MASK_ALL) = 0;
	virtual int		get_points_contents_collidable(i_collidable* pCollide, const Vector& vecAbsPosition) = 0;
	virtual void	clip_ray_to_entity(const Ray_t& ray, unsigned int fMask, i_handle_entity* pEnt, trace_t* pTrace) = 0;
	virtual void	clip_ray_to_collidable(const Ray_t& ray, unsigned int fMask, i_collidable* pCollide, trace_t* pTrace) = 0;
	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	trace_ray(const Ray_t& ray, unsigned int fMask, c_trace_filter* pTraceFilter, trace_t* pTrace) = 0;
	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void	setup_leaf_and_entity_trace_ray(const Ray_t& ray, void* pTraceData) = 0;
	virtual void    setup_leaf_and_entity_list_box(const Vector& vecBoxMin, const Vector& vecBoxMax, void* pTraceData) = 0;
	virtual void	setup_leaf_and_entity_and_entity_list(const Ray_t& ray, void* pTraceData, unsigned int fMask, c_trace_filter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void	sweep_collidable(i_collidable* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd,const QAngle& vecAngles, unsigned int fMask, c_trace_filter* pTraceFilter, trace_t* pTrace) = 0;
	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void	enumerate_entities(const Ray_t& ray, bool triggers, void* pEnumerator) = 0;
	virtual void	enumerate_entities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, void* pEnumerator) = 0;
	virtual i_collidable* GetCollideable(i_handle_entity* pEntity) = 0;
	virtual int get_stat_by_index(int index, bool bClear) = 0;
	virtual void get_brush_in_aabb(const Vector& vMins, const Vector& vMaxs, void*& BrushQuery, int iContentsMask = 0xFFFFFFFF, int cmodelIndex = 0) = 0;
	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual void* pSkip000(const Vector& vMins, const Vector& vMaxs) = 0;
	virtual int pSkip001() = 0;
	virtual void pSkip002(int nIndex, void* pMeshTriList) = 0;
	virtual int get_brush_info(int iBrush, int& ContentsOut, void* pBrushSideInfoOut, int iBrushSideInfoArraySize) = 0;
	virtual bool point_outside_world(const Vector& ptTest) = 0; //Tests a point to see if it's outside any playable area
	// Walks bsp to find the leaf containing the specified point
	virtual int pSkip003(const Vector& ptTest) = 0;
	virtual void* alloca_trace_data() = 0;
	virtual void free_trace_list_data(void*) = 0;
	virtual int get_set_debug_trace_counter(int value, void* behavior) = 0;
	virtual int pSkip004(const Vector& vMins, const Vector& vMaxs, void* pOutputMeshes, int iMaxOutputMeshes) = 0;
	virtual void get_brush_in_collidable(i_collidable* pCollideable, void*& BrushQuery) = 0;
	virtual bool is_fullu_occuled(int nOcclusionKey, const void*& aabb1, const void*& aabb2, const Vector& vShadow) = 0;
	virtual void suspend_occlusion_tests() = 0;
	virtual void resume_occlusion_tests() = 0;
	virtual void flush_occlusion_tests() = 0;
};
#define IENGINEINTERFACE "EngineTraceClient004"