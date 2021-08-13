#pragma once

#include "../../../util/exec.cpp"
#include <string>
#include <regex>

using namespace std;

namespace Util {
  namespace Windows {
    namespace Exe {
      void install(const char* name) {
        string start = "%TMP%/bytecube/";
        string end = "/installer.exe";

        string command = start + name + end;
        exec(command.c_str());
      }
    }
  }
}