#pragma once

#include "../../../util/exec.cpp"
#include <string>
#include <regex>

using namespace std;

namespace Util {
  namespace Windows {
    namespace Exe {
      void install(const char* name) {
        #ifdef __CYGWIN__
          string start = "/tmp/bytecube/";
        #else
          string start = "%TMP%/bytecube/";
        #endif
        string end = "/installer.exe";

        string command = start + name + end;
        exec(command.c_str());
      }
    }
  }
}