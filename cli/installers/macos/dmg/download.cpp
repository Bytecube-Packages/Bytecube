#include "../../../util/exec.cpp"
using namespace std;

string al_encode(const string &value) {
  string output = "";

  for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
    string::value_type c = (*i);

    if (c == ' ') continue;
    if (c > 32) continue;
    output += to_string(int((unsigned char) c));
    output += " ";
  }

  return output;
}

void download_percentages(const char* cmd, void (*progress)(int)) {
  array<char, 32> buffer;
  string result = "";
  bool str = true;
  int p = 0;

  string t = "";

  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    string current = buffer.data();
    result += current;

    for (int i = 0; i < current.size(); i++) {
      char c = current[i];

      // cout << int(c) << " " << (int(c) == 13) << endl;

      if (int(c) == 13) {
        cout << t << endl;
        cout << "This is: " << 13 << endl;
        // (*progress)(p);
        str = true;
        p = 0;
        t = "";
        continue;
      }
      if (int(c) == 32 && str) continue;
      if (!isdigit(c)) {
        //(*progress)(p);
        // cout << p << endl;
        break;
      }

      t += c;

      // str = false;
      // p = p * 10 + (c - '0');
    }
  }
  // cout << al_encode(result) << endl;
}

namespace Installer {
  namespace Macos {
    namespace Dmg {
      void download(string url, void (*progress)(int)) {
        string begining = "curl --output /tmp/bytecube-installed-package.dmg";
        string cmd = begining + " " + url + " 2>&1";

        download_percentages(cmd.c_str(), progress);
      }
    }
  }
}