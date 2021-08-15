#pragma once

#include "../../../util/exec.cpp"
#include <string>
#include <regex>

using namespace std;

namespace Util {
  namespace Macos {
    namespace Dmg {
      string attach(const char* name) {
        string start = "hdiutil attach -nobrowse";

        string command = start + " " + name;
        string volume = exec(command.c_str());

        string r = "\\/Volumes\\/(\\s?\\w+)*";
        smatch m;
        regex_search(volume, m, regex(r));
        
        return regex_replace(m.str(), regex("\\s"), "\\ ");
      }

      void copy(const char* volume, const char* name) {
        string start = "cp -rf ";
        string end = "/*.app /tmp/bytecube/" + string(name) + "/apps 2>&1";

        string command = start + volume + end;
        exec(command.c_str());
      }

      void detach(const char* name) {
        string start = "hdiutil detach ";
        string command = start + name;

        exec(command.c_str());
      }
    }
  }
}