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
  namespace Windows {
    namespace Exe {
      #ifdef WINDOWS
        void unpackage(string name) {
          cout << endl;
          cout << "Installing exe..." << endl;

          Util::Windows::Exe::install(name.c_str());
        }
      #else
        void unpackage(string name) {}
      #endif
    }
  }
}