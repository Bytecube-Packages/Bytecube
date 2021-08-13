#pragma once

#include "../../util/exec.cpp"
#include <string>

using namespace std;

namespace Util {
  namespace Windows {
    void create(const char* name) {
      exec("md \"%TMP%/bytecube/" + string(name) + "\" 2>&1");
    }

    void remove(const char* name) {
      exec("rd /s /q \"%TMP%/bytecube/" + string(name) + "\" 2>&1");
    }
  }
}