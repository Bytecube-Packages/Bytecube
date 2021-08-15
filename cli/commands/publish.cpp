#include <iostream>
#include <string>

#include "../util/colors.cpp"
#include "../util/package.cpp"
using namespace std;

namespace Command {
  class Publish {
    public:
      static void run(string package) {
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

        string macos = input("Macos url (leave empty if none)");
        string windows = input("Windows url (leave empty if none)");
        string linux = input("Linux url (leave empty if none)");

        InstallerOptions options;
        options.macos = getInstallOption(macos);
        options.windows = getInstallOption(windows);
        options.linux = getInstallOption(linux);

        Json pkg = createPackage(info, options);
        cout << "Package Json: " << pkg.stringify() << endl;

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