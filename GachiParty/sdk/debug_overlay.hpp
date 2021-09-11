#pragma once
#include "vector.h"
#define VDEBUG_OVERLAY_INTERFACE_VERSION	"VDebugOverlay004"
class c_debug_overlay
{
public:
	virtual void* unkn0() = 0;
	virtual void* unkn1() = 0;
	virtual void add_box_overlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void* unkn3() = 0;
	virtual void* unkn4() = 0;
	virtual void add_line_overlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void add_text_overlay(const Vector& origin, float duration,  const char* format, ...) = 0;
	virtual void* add_text_overlay_undefined() = 0;//i:7
	virtual void* unk8() = 0;
	virtual void* unk9() = 0;
	virtual void* unk10() = 0;
	virtual void* unk11() = 0;
	virtual int screen_position(const Vector& point, Vector& screen) = 0;
	virtual int screen_position(float x_pos, float y_pos, Vector& screen) = 0;
};