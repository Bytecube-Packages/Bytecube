#include "./exec.cpp"
#include "./url_encode.cpp"
#include <iostream>

#include "./os.cpp"

#include "../installers/macos/dmg/download.cpp"
#include "../installers/macos/dmg/unpackage.cpp"

#include "../installers/windows/exe/download.cpp"
#include "../installers/windows/exe/unpackage.cpp"

using namespace std;

namespace Installer {
  string getUrl(string platform, string package) {
    string start = "curl -s \"localhost:3000/package/install";
    string end = "\"";

    string platform_param = "?platform=" + url_encode(platform);
    string package_param = "&package=" + package;

    string cmd = start + platform_param + package_param + end;
    string url = exec(cmd.c_str());

    if (url.empty()) throw runtime_error("Failed to fetch package url");
    if (url[0] != '"') throw runtime_error("An Error occured while fetching url");
    return url;
  }

  bool fetchPackage(string package, void (*progress)(int)) {
    try {
      string url = getUrl(os, package);

      if (isMacos) {
        Macos::Dmg::download(package, url, progress);
        return true;
      }
      if (isWindows) {
        Windows::Exe::download(package, url, progress);
        return true;
      }
      return false;
    } catch (string error) {
      cerr << error << endl;
      return false;
    }
  }

  bool installPackage(string package, void (*progress)(int)) {
    package = url_encode(package);

    if (fetchPackage(package, progress)) {
      if (isMacos) {
        Macos::Dmg::unpackage(package);
        return true;
      }
      if (isWindows) {
        Windows::Exe::unpackage(package);
        return true;
      }
    }

    return false;
  }
}