#pragma once

#include "../../util/exec.cpp"
#include <string>

using namespace std;

namespace Util {
  namespace Windows {
    #ifdef __CYGWIN__
      void create(const char* name) {
        exec("mkdir -p /tmp/bytecube/" + string(name) + " 2>&1");
      }

      void remove(const char* name) {
        exec("rm -r /tmp/bytecube/" + string(name) + " 2>&1");
      }
    #else
      void create(const char* name) {
        exec("md \"%TMP%/bytecube/" + string(name) + "\" 2>&1");
      }

      void remove(const char* name) {
        exec("rd /s /q \"%TMP%/bytecube/" + string(name) + "\" 2>&1");
      }
    #endif
  }
}