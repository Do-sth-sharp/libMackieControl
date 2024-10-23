#pragma once

#if defined (__clang__)
#define MACKIE_CLANG 1

#elif defined (__GNUC__)
#define MACKIE_GCC 1

#elif defined (_MSC_VER)
#define MACKIE_MSVC 1

#else
#error Unknown cpp compiler
#endif

#if (defined (_WIN32) || defined (_WIN64)) && !defined (__MINGW32__)
#define MACKIE_Export __declspec(dllexport)
#define MACKIE_Import __declspec(dllimport)
#else
#define MACKIE_Export __attribute__((visibility("default")))
#define MACKIE_Import __attribute__((visibility("default")))
#endif

#if MACKIE_MSVC
#define MACKIE_Call _cdecl
#else
#define MACKIE_Call
#endif

#if MACKIE_DLL_BUILD
#define MACKIE_API MACKIE_EXPORT
#elif MACKIE_DLL
#define MACKIE_API MACKIE_IMPORT
#else
#define MACKIE_API 
#endif // MACKIE_DLL_BUILD
