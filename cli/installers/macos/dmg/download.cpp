#include "../../../util/exec.cpp"
#include "./util.cpp"

using namespace std;

void download_percentages(const char* cmd, void (*progress)(int)) {
  (*progress)(0);

  array<char, 32> buffer;
  bool str = true;
  bool new_line = true;
  int p = 0;

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) throw runtime_error("popen() failed!");
  
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    string current = buffer.data();

    for (int i = 0; i < current.size(); i++) {
      char c = current[i];

      if (int(c) == 13) {
        (*progress)(p);

        new_line = true;
        str = true;
        p = 0;
        continue;
      }

      if (!new_line) continue;

      if (c == ' ' && str) continue;
      if (c == ' ') new_line = false;

      if (isdigit(c)) {
        str = false;
        p = p * 10 + int(c) - '0';
      }
    }
  }

  (*progress)(100);
}

namespace Installer {
  namespace Macos {
    namespace Dmg {
      void download(string name, string url, void (*progress)(int)) {
        Util::Dmg::remove(name.c_str());
        exec("mkdir -p /tmp/bytecube/" + name + "/apps");

        string begining = "curl -L --output /tmp/bytecube/" + name + "/installer.dmg";
        string cmd = begining + " " + url + " 2>&1";

        download_percentages(cmd.c_str(), progress);
      }
    }
  }
}