#pragma once

#include "./exec.cpp"
#include "./url_encode.cpp"
#include <iostream>

#include "./colors.cpp"
#include "./api.cpp"
#include "./os.cpp"

#include "../installers/macos/dmg/download.cpp"
#include "../installers/macos/dmg/unpackage.cpp"

#include "../installers/macos/pkg/download.cpp"
#include "../installers/macos/pkg/unpackage.cpp"

#include "../installers/windows/exe/download.cpp"
#include "../installers/windows/exe/unpackage.cpp"

#include "../installers/windows/msi/download.cpp"
#include "../installers/windows/msi/unpackage.cpp"

#include "json.cpp"
#include "to_http.cpp"

using namespace Util;
using namespace std;

struct PackageInfo {
  string name;
  string description;
  string version;
};

struct InstallOption {
  string url;
  string type;
};

struct InstallerOptions {
  InstallOption* macos;
  InstallOption* windows;
  InstallOption* linux;
};

namespace Installer {
  InstallOption getInstall(string platform, string package) {
    map<string, string> params;
    params["platform"] = platform;
    params["package"] = package;

    string start = "curl -s -k \"" + api + "/package/install";
    string end = "\"";

    string cmd = start + to_http(params, false) + end;
    string data = exec(cmd.c_str());

    Json json = Json::parse(data);
    if (json.type != "object") throw "Invalid response";

    map<string, Json> json_map = json.getMap();
    if (json_map.find("error") != json_map.end()) {
      string raw_error = json_map["error"].getValue("Unknown Error");
      string error = "Error: " + raw_error;

      throw error;
    }

    string url = json_map["url"].getValue("");
    string type = json_map["type"].getValue("");

    if (url.empty() || type.empty()) throw "Invalid response";

    return {
      url, 
      type
    };
  }

  bool fetchPackage(string package, InstallOption install, void (*progress)(int)) {
    try {
      if (isMacos) {
        if (install.type == "dmg") Macos::Dmg::download(package, install.url, progress);
        if (install.type == "pkg") Macos::Pkg::download(package, install.url, progress);
        return true;
      }
      if (isWindows) {
        if (install.type == "exe") Windows::Exe::download(package, install.url, progress);
        if (install.type == "msi") Windows::Msi::download(package, install.url, progress);
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
    InstallOption install;
    try {
      install = getInstall(os, package);
    } catch (string error) {
      set_color(31);
      set_bold(true);
      cerr << error << endl;

      set_color(0);
      return false;
    }

    if (fetchPackage(package, install, progress)) {
      cout << endl;
      if (isMacos) {
        if (install.type == "dmg") Macos::Dmg::unpackage(package);
        if (install.type == "pkg") Macos::Pkg::unpackage(package);
        return true;
      }
      if (isWindows) {
        if (install.type == "exe") Windows::Exe::unpackage(package);
        if (install.type == "msi") Windows::Msi::unpackage(package);
        return true;
      }
    }

    return false;
  }
}

InstallOption* getInstallOption(string url) {
  if (url.length() < 1) return nullptr;

  string type = "";
  for (int i = url.length() - 1; i >= 0; i--) {
    if (url[i] == '.') {
      type = url.substr(i + 1);
      break;
    }
  }

  if (type.length() > 3) type = "";

  InstallOption* option = new InstallOption;
  option->url = url;
  option->type = type;

  return option;
}


Json createInstallerOption(InstallOption options) {
  map<string, Json> installer;
  installer["url"] = Json(options.url);
  installer["type"] = Json(options.type);

  return Json(installer);
}
Json createInstallerOptions(InstallerOptions installer) {
  map<string, Json> options;
  if (installer.macos) options["macos"] = createInstallerOption(*installer.macos);
  if (installer.windows) options["windows"] = createInstallerOption(*installer.windows);
  if (installer.linux) options["linux"] = createInstallerOption(*installer.linux);

  return Json(options);
}
Json createInformation(PackageInfo info) {
  map<string, Json> information;
  information["name"] = Json(info.name);
  information["description"] = Json(info.description);
  information["version"] = Json(info.version);

  return Json(information);
}

Json createPackage(PackageInfo info, InstallerOptions installers) {
  map<string, Json> main;
  main["info"] = createInformation(info);
  main["install"] = createInstallerOptions(installers);

  return Json(main);
}

void publishPackage(Json package) {
  string json = package.stringify();
  string cmd = "curl -s -k -H \"Content-Type: application/json\" -X POST -d \"" + escape(json) + "\" \"" + api + "/package/publish\" ";

  string result = exec(cmd.c_str());
  Json jsonResult = Json::parse(result);

  if (jsonResult.type == "object") {
    set_bold(true);
    set_color(31);
    cerr << "Error: " << jsonResult.getMap()["error"].getValue("No Error") << endl;
    set_color(0);

    exit(1);
  }
}