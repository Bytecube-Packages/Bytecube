#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "../util/colors.cpp"
#include "../util/package.cpp"

using namespace std;

namespace Command {
  class Install {
    public:
      static void run(string package, set<string> flags) {
        cout << "Installing \"";

        set_color(accent);
        cout << package;

        reset();
        cout << "\"" << endl;


        // actually install the package
        if (!Installer::installPackage(package, display_progress, flags.find("keep") != flags.end(), flags.find("download-only") != flags.end())) exit(1);

        reset();
        set_color(accent);
        set_bold(true);
              
        reset();
      }
    private:
      static void display_progress(int procent) {
        int width = 20;
        int progress = (procent * width) / 100;

        cout << "\r";

        set_color(accent);
        set_color(accent + 10);
        for (int i = 0; i < progress; i++) {
          cout << ".";
        }
        reset();
        for (int i = progress; i < width; i++) {
          cout << ".";
        }

        set_bold(true);

        int len = to_string(procent).length();
        for (int i = 0; i < (3 - len); i++) cout << " ";

        cout << " " << procent << "%" << flush;
      }
  };
}