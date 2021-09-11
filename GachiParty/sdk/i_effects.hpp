#pragma once
#include "vector.h"
#define IEFFECTS_INTERFACE_VERSION	"IEffects001"

#define MUZZLEFLASH_TYPE_DEFAULT	0x00000001
#define MUZZLEFLASH_TYPE_GUNSHIP	0x00000002
#define MUZZLEFLASH_TYPE_STRIDER	0x00000004
class i_prediction_system
{
public:
	virtual ~i_prediction_system() {};
private:

};

class i_effects : public i_prediction_system
{
public:
	virtual void beam(const Vector & Start, const Vector & End, int nModelIndex,
		int nHaloIndex, unsigned char frameStart, unsigned char frameRate,
		float flLife, unsigned char width, unsigned char endWidth, unsigned char fadeLength,
		unsigned char noise, unsigned char red, unsigned char green,
		unsigned char blue, unsigned char brightness, unsigned char speed) = 0;
	//-----------------------------------------------------------------------------
	// Purpose: Emits smoke sprites.
	// Input  : origin - Where to emit the sprites.
	//			scale - Sprite scale * 10.
	//			framerate - Framerate at which to animate the smoke sprites.
	//-----------------------------------------------------------------------------
	virtual void smoke(const Vector& origin, int modelIndex, float scale, float framerate) = 0;
	virtual void sparks(const Vector& position, int nMagnitude = 1, int nTrailLength = 1, const Vector* pvecDir = NULL) = 0;
	virtual void dust(const Vector& pos, const Vector& dir, float size, float speed) = 0;
	virtual void muzzleFlash(const Vector& vecOrigin, const QAngle& vecAngles, float flScale, int iType) = 0;
	// like ricochet, but no sound
	virtual void metalSparks(const Vector& position, const Vector& direction) = 0;
	virtual void energySplash(const Vector& position, const Vector& direction, bool bExplosive = false) = 0;
	virtual void ricochet(const Vector& position, const Vector& direction) = 0;
	virtual float time() = 0;
	virtual bool isServer() = 0;
	virtual void suppressEffectsSounds(bool bSuppress) = 0;
};