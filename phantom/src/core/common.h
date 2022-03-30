#pragma once

#include <memory>

#define IMGUI_IMPL_OPENGL_LOADER_GLBINDING3
#define GLFW_INCLUDE_NONE

#define PH_NAMESPACE_BEGIN \
namespace ph \
{

#define PH_NAMESPACE_END }

//Debug
#ifdef PH_DEBUG
    #if defined(PH_PLATFORM_WINDOWS)
        #define debug_break() __debugbreak()
    #elif defined(PH_PLATFORM_LINUX)
        #include <signal.h>
        #define debug_break() raise(SIGTRAP)
    #elif defined(PH_PLATFORM_MACOSX)
        #define debug_break() __builtin_trap()
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define PH_ASSERT
#else
#define debug_break()
#endif

#define BIT(x) (1 << x)

//Platform detector
#ifdef _WIN32
    #ifdef _WIN64
        #define PH_PLATFORM_WINDOWS
    #else
        #error windows 32-bits not supported!
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define PH_PLATFORM_MACOS
#elif defined(__linux__)
    #define PH_PLATFORM_LINUX
#endif

// Type Definitions
using uint = unsigned int;
using ulong = unsigned long;
using ushort = unsigned short;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T>
using unique = std::unique_ptr<T>;