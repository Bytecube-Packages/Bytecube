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
    namespace Pkg {
      #ifdef MACOS
        void unpackage(string name) {
          cout << "Installing pkg..." << endl;

          string file = "/tmp/bytecube/" + name + "/installer.pkg";
          Util::Macos::Pkg::install(file.c_str());
          Util::Macos::remove(name.c_str());
        }
      #else
        void unpackage(string name) {}
      #endif
    }
  }
}