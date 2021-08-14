#pragma once

#include "../../../util/exec.cpp"
#include <string>
#include <regex>

using namespace std;

namespace Util {
  namespace Windows {
    namespace Msi {
      void install(const char* name) {
        string start = "cd %TMP%/bytecube/";
        string end = " && msiexec /i installer.msi";

        string command = start + name + end;
        exec(command.c_str());
      }
    }
  }
}