#pragma once

#include <string>
using namespace std;

#if defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN__)
  string os = "windows";
  const bool isWindows = true;
  const bool isMacos = false;
  const bool isLinux = false;
  #define WINDOWS
#else 
  #ifdef __APPLE__
    string os = "macos";
    const bool isWindows = false;
    const bool isMacos = true;
    const bool isLinux = false;
    #define MACOS
  #else
    #ifdef __linux__
      string os = "linux";
      const bool isWindows = false;
      const bool isMacos = false;
      const bool isLinux = true;
      #define LINUX
    #else
      string os = "unknown";
      const bool isWindows = false;
      const bool isMacos = false;
      const bool isLinux = false;
    #endif
  #endif
#endif