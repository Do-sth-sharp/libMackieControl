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

#if MACKIE_MSVC
#define MACKIE_EXPORT __declspec(dllexport)
#define MACKIE_IMPORT __declspec(dllimport)
#define MACKIE_CALL _cdecl
#endif

#if MACKIE_CLANG
#define MACKIE_EXPORT __attribute__((visibility("default")))
#define MACKIE_IMPORT __attribute__((visibility("default")))
#define MACKIE_CALL
#endif

#if MACKIE_GCC
#define MACKIE_EXPORT __attribute__((visibility("default")))
#define MACKIE_IMPORT __attribute__((visibility("default")))
#define MACKIE_CALL
#endif

#if !(MACKIE_MSVC || MACKIE_CLANG || MACKIE_GCC)
#define MACKIE_EXPORT 
#define MACKIE_IMPORT 
#define MACKIE_CALL
#endif

#if MACKIE_DLL_BUILD
#define MACKIE_API MACKIE_EXPORT
#elif MACKIE_DLL
#define MACKIE_API MACKIE_IMPORT
#else
#define MACKIE_API 
#endif // MACKIE_DLL_BUILD
