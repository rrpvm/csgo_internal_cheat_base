#include "utils.hpp"
#include <vector>
#include <Psapi.h>
#include "sdk/sdk.hpp"
std::uint8_t* Utilities::PatternScan(void* module, const char* signature)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dosHeader = (PIMAGE_DOS_HEADER)module;
    auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

    auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto patternBytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scanBytes[i];
        }
    }
    return nullptr;
}
trace_t Utilities::trace_ray_utl(void* skip, Vector& p, Vector& end, uint32_t mask)
{
    Ray_t ray; c_trace_filter filter; trace_t trace;
    filter.skip = skip;
    ray.Init(p, end);
    Interfaces::g_trace->trace_ray(ray, mask, &filter, &trace);
    return trace;
}
 void Utilities::vec_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{  
        out[0] = in1.Dot(Vector(in2[0])) + in2[0][3];
        out[1] = in1.Dot(Vector(in2[1])) + in2[1][3];
        out[2] = in1.Dot(Vector(in2[2])) + in2[2][3];   
}
uintptr_t Utilities::pattern_scan(const char* module_name, const BYTE* pattern, const char* mask)
{
    MODULEINFO module_info;
    const unsigned int module_address = reinterpret_cast<unsigned int>(GetModuleHandle(module_name)); 
    GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_address), &module_info, sizeof(MODULEINFO));
    bool bFind = false;
    const size_t length = strlen(mask);
    for (size_t i = module_address; i < module_address + module_info.SizeOfImage - length; ++i)
    {
        bFind = true;
        for (size_t j = 0; j < length; ++j)
        {
            if (mask[j] == 'x' && pattern[j] != *(unsigned char*)(i + j))
            {
                bFind = false;
                break;
            }                      
        }
        if (bFind)return i;
    }
    return -1;
}
