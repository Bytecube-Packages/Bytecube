#include "./exec.cpp"
#include "./url_encode.cpp"
#include <iostream>

#include "./os.cpp"

#include "../installers/macos/dmg/download.cpp"
#include "../installers/macos/dmg/unpackage.cpp"

#include "../installers/windows/exe/download.cpp"
#include "../installers/windows/exe/unpackage.cpp"

#include "../installers/windows/msi/download.cpp"
#include "../installers/windows/msi/unpackage.cpp"

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
  string getMeta(string platform, string package) {
    string start = "curl -s \"localhost:3000/package/meta";
    string end = "\"";

    string platform_param = "?platform=" + url_encode(platform);
    string package_param = "&package=" + package;

    string cmd = start + platform_param + package_param + end;
    string meta = exec(cmd.c_str());

    if (meta.empty()) throw runtime_error("Failed to fetch package meta");
    if (meta[0] != '"') throw runtime_error("An Error occured while fetching meta");
    return meta;
  }

  bool fetchPackage(string package, string meta, void (*progress)(int)) {
    try {
      string url = getUrl(os, package);

      if (isMacos) {
        if (meta == "dmg") Macos::Dmg::download(package, url, progress);
        return true;
      }
      if (isWindows) {
        if (meta == "exe") Windows::Exe::download(package, url, progress);
        if (meta == "msi") Windows::Msi::download(package, url, progress);
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

    string meta = getMeta(os, package);
    meta = meta.substr(1, meta.size() - 2);

    if (fetchPackage(package, meta, progress)) {
      if (isMacos) {
        if (meta == "dmg") Macos::Dmg::unpackage(package);
        return true;
      }
      if (isWindows) {
        if (meta == "exe") Windows::Exe::unpackage(package);
        if (meta == "msi") Windows::Msi::unpackage(package);
        return true;
      }
    }

    return false;
  }
}