#include <iostream>
#include <string>

#include "../util/colors.cpp"
#include "../util/package.cpp"
using namespace std;

namespace Command {
  class Publish {
    public:
      static void run(string package, set<string> flags) {
        if (os == "unknown") {
          cout << "Unknown OS" << endl;
          return;
        }

        cout << "Preparing \"";

        set_color(accent);
        cout << package;

        set_color(0);
        cout << "\"" << endl;

        string description = input("Description");
        string version = input("Version");

        PackageInfo info = { package, description, version };

        InstallerOptions options;
        string macos = input("Macos url (leave empty if none)");
        options.macos = getInstallOption(macos);
        if (options.macos != nullptr && options.macos->type == "") {
          string type = input("Macos type");
          options.macos->type = type;
        }

        string windows = input("Windows url (leave empty if none)");
        options.windows = getInstallOption(windows);
        if (options.windows != nullptr && options.windows->type == "") {
          string type = input("Windows type");
          options.windows->type = type;
        }

        string linux = input("Linux url (leave empty if none)");
        options.linux = getInstallOption(linux);
        if (options.linux != nullptr && options.linux->type == "") {
          string type = input("Linux type");
          options.linux->type = type;
        }

        Json pkg = createPackage(info, options);

        publishPackage(pkg);

        set_color(0);
        set_color(accent);
        set_bold(true);
        cout << "Finished" << endl;

        set_color(0);
      }
    private:
      static string input(string message) {
        set_color(0);
        set_bold(true);
        cout << message;
        cout << " > ";

        string value;
        set_color(accent);

        getline(cin, value);
        set_color(0);
        return value;
      }
  };
}