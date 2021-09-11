#pragma once
#include <Windows.h>
#include <string>
#include "sdk/c_game_trace.hpp"
#include "sdk/matrix.hpp"
class Utilities {
public:
	uintptr_t pattern_scan(const char* module_name, const BYTE* pattern , const char* mask);
	std::uint8_t* PatternScan(void* module, const char* signature);//csgosimple
	trace_t trace_ray_utl(void* skip,  Vector& p, Vector& end, uint32_t mask);
	static void vec_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
private:
};
inline Utilities utils;