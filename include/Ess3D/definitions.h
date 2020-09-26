#pragma once

#if defined (__GNUC__)
  #define API __attribute__ ((__visibility__("default")))
#elif defined (WIN32)
#ifdef Ess3D_EXPORTS
  #define API __declspec(dllexport)
  #else
  #define API __declspec(dllimport)
  #endif
#endif

#define GLM_FORCE_RADIANS
