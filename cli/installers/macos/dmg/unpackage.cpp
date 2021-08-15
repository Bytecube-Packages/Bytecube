#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

#include "../../../util/os.cpp"
#include "./util.cpp"
#include "../util.cpp"

using namespace std;

namespace Installer {
  namespace Macos {
    namespace Dmg {
      #ifdef MACOS
        void unpackage(string name) {
          cout << "Unpacking dmg..." << endl;

          string file = "/tmp/bytecube/" + name + "/installer.dmg";
          string volume = Util::Macos::Dmg::attach(file.c_str());
          Util::Macos::Dmg::copy(volume.c_str(), name.c_str());
          Util::Macos::Dmg::detach(volume.c_str());

          Util::Macos::move(name.c_str());
          Util::Macos::remove(name.c_str());
        }
      #else
        void unpackage(string name) {}
      #endif
    }
  }
}