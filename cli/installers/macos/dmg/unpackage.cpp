#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

#include "./util.cpp"

using namespace std;

namespace Installer {
  namespace Macos {
    namespace Dmg {
      void unpackage(string name) {
        cout << endl;
        cout << "Unpacking dmg..." << endl;

        string file = "/tmp/bytecube/" + name + "/installer.dmg";
        string volume = Util::Dmg::attach(file.c_str());
        Util::Dmg::copy(volume.c_str(), name.c_str());
        Util::Dmg::detach(volume.c_str());
        Util::Dmg::move(name.c_str());
        Util::Dmg::remove(name.c_str());
      }
    }
  }
}