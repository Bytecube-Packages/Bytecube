#include <iostream>
#include <string>

#include "../util/colors.cpp"
#include "../util/package.cpp"
using namespace std;

namespace Command {
  class Install {
    public:
      static void run(string package) {
        cout << "Installing \"";

        set_color(accent);
        cout << package;

        set_color(0);
        cout << "\"" << endl;

        // actually install the package
        Installer::installPackage("macos", package, display_progress);

        cout << endl;

        set_color(0);
        set_color(accent);
        cout << "Finished" << endl;

        set_color(0);
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
        set_color(0);
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