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
    namespace Msi {
      #ifdef WINDOWS
        void unpackage(string name, bool keep) {
          cout << "Running msi..." << endl;

          Util::Windows::Msi::install(name.c_str());
          if (!keep) Util::Windows::remove(name.c_str());
        }
      #else
        void unpackage(string name, bool keep) {}
      #endif
    }
  }
}