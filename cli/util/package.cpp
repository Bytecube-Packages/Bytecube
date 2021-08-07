#include "./exec.cpp"
#include "./url_encode.cpp"
#include <iostream>

#include "../installers/macos/dmg/download.cpp"

using namespace std;

namespace Installer {
  string getUrl(string platform, string package) {
    string start = "curl -s \"localhost:3000/package/install";
    string end = "\"";

    string platform_param = "?platform=" + url_encode(platform);
    string package_param = "&package=" + url_encode(package);

    string cmd = start + platform_param + package_param + end;
    string url = exec(cmd.c_str());

    if (url.empty()) throw runtime_error("Failed to fetch package url");
    if (url[0] != '"') throw runtime_error("An Error occured while fetching url");
    return url;
  }

  bool fetchPackage(string platform, string package, void (*progress)(int)) {
    try {
      string url = getUrl(platform, package);

      if (platform == "macos") {
        Macos::Dmg::download(url, progress);
        return true;
      }
      return false;
    } catch (string error) {
      cerr << error << endl;
      return false;
    }
  }
}