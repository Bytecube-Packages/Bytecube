#pragma once

#include "../../../util/exec.cpp"
#include <string>
#include <regex>

using namespace std;

namespace Util {
  namespace Macos {
    namespace Pkg {
      void install(const char* file) {
        string start = "sudo installer -pkg";
        string end = "-target / 2>&1";

        string command = start + " " + file + " " + end;
        exec(command.c_str());
      }
    }
  }
}