#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

#include "../../../util/exec.cpp"

using namespace std;

namespace Util {
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

    void copy(const char* name) {
      string start = "cp -rf ";
      string end = "/*.app /Applications";

      string command = start + name + end;
      exec(command.c_str());
    }

    void detach(const char* name) {
      string start = "hdiutil detach ";
      string command = start + name;

      exec(command.c_str());
    }

    void remove(const char* name) {
      string start = "rm";
      string command = start + " " + name;
      exec(command.c_str());
    }
  }
}

namespace Installer {
  namespace Macos {
    namespace Dmg {
      void unpackage() {
        cout << endl;
        cout << "Unpacking dmg..." << endl;

        string file = "/tmp/bytecube-installed-package.dmg";
        string volume = Util::Dmg::attach(file.c_str());
        Util::Dmg::copy(volume.c_str());
        Util::Dmg::detach(volume.c_str());
        Util::Dmg::remove(file.c_str());
      }
    }
  }
}