#pragma once

#include "../../util/exec.cpp"
#include <string>

using namespace std;

namespace Util {
  namespace Macos {
    void create(const char* name) {
      exec("mkdir -p /tmp/bytecube/" + string(name) + "/apps 2>&1");
    }

    void move(const char* name) {
      exec("mv /tmp/bytecube/" + string(name) + "/apps/* /Applications 2>&1");
    }

    void remove(const char* name) {
      exec("rm -r /tmp/bytecube/" + string(name) + " 2>&1");
    }
  }
}