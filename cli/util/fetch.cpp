#include "./exec.cpp"
#include <iostream>

using namespace std;

int main() {
  string url = exec("curl -s \"localhost:3000/package/install?platform=macos&package=chrome\"");

  if (url.empty()) return 1;
  if (url[0] != '"') return 1;

  string begining = "curl -s --output /tmp/bytecube-installed-package.dmg ";
  string cmd = begining + url;

  exec(cmd.c_str());
}