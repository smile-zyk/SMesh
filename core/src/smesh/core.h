#pragma once

#ifdef SMESH_PLATFORM_WINDOWS
    #ifdef SMESH_BUILD_LIBRARY
        #define SMESH_API __declspec(dllexport)
    #else
        #define SMESH_API __declspec(dllimport)
    #endif
#endif