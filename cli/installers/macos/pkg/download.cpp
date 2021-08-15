#include "../../../util/download_progress.cpp"
#include "../util.cpp"

using namespace std;


namespace Installer {
  namespace Macos {
    namespace Pkg {
      #ifdef MACOS
        void download(string name, string url, void (*progress)(int)) {
          Util::Macos::remove(name.c_str());
          Util::Macos::create(name.c_str());

          string begining = "-L --output /tmp/bytecube/" + name + "/installer.pkg";
          string cmd = begining + " " + url + " 2>&1";

          Util::download_progress(cmd.c_str(), progress);
        }
      #else
        void download(string name, string url, void (*progress)(int)) {}
      #endif
    }
  }
}