#include "../../../util/download_progress.cpp"
#include "../util.cpp"

using namespace std;


namespace Installer {
  namespace Windows {
    namespace Exe {
      #ifdef WINDOWS
        void download(string name, string url, void (*progress)(int)) {
          Util::Windows::remove(name.c_str());
          Util::Windows::create(name.c_str());

          #ifdef __CYGWIN__
            string begining = "-L --output /tmp/bytecube/" + name + "/installer.exe";
          #else
            string begining = "-L --output %TMP%/bytecube/" + name + "/installer.exe";
          #endif

          string cmd = begining + " " + url + " 2>&1";

          Util::download_progress(cmd.c_str(), progress);
        }
      #else
        void download(string name, string url, void (*progress)(int)) {}
      #endif
    }
  }
}