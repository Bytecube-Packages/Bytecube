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

        reset();
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

        publishPackage(pkg);

        reset();
        set_color(accent);
        set_bold(true);
        cout << "Finished" << endl;

        reset();
      }
    private:
      static string input(string message) {
        reset();
        set_bold(true);
        cout << message;
        cout << " > ";

        string value;
        set_color(accent);

        getline(cin, value);
        reset();
        return value;
      }
  };
}