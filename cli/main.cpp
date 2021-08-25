#include <iostream>
#include <stdlib.h>
#include <string>
#include <set>
#include "./util/colors.cpp"

#include "./commands/login.cpp"
#include "./commands/add.cpp"
#include "./commands/publish.cpp"
using namespace std;

void error() {
  set_color(31);
  cerr << "Usage: bytecube [login | install | publish]" << endl;
  reset();
}
void error(string message) {
  set_color(31);
  cerr << "Usage: bytecube " << message << endl;
  reset();
}

map<string, set<string>> flags = {
  {
    // flag name
    "keep",

    // flag values
    {
      "--keep",
      "-k"
    }
  },
  {
    // flag name
    "download-only",

    // flag values
    {
      "--download-only",
      "-d"
    }
  }
};

vector<string> getFlags(int argv, char** argc, int start) {
  vector<string> flags;

  for (int i = start; i < argv; i++) {
    string arg = argc[i];
    if (arg.substr(0, 1) == "-") flags.push_back(arg);
  }

  return flags;
}

set<string> parseFlags(vector<string> f) {
  set<string> parsedFlags;

  for (string flag : f) {
    for (auto it = flags.begin(); it != flags.end(); it++) {
      if (it->second.find(flag) != it->second.end()) {
        parsedFlags.insert(it->first);
      }
    }
  }

  return parsedFlags;
}

set<string> parseFlags(int argv, char** argc, int start) {
  return parseFlags(getFlags(argv, argc, start));
}


int main(int argc, char** argv) {
  if (os == "unknown") {
    cout << "Unknown OS" << endl;
    return EXIT_SUCCESS;
  }

  reset();
  set_bold(true);
  if (argc < 2) {
    error();
    return EINVAL;
  }
  if (strcmp(argv[1], "login") == 0) {
    Command::Login::run(parseFlags(argc, argv, 2));
    return EXIT_SUCCESS;
  }
  if (strcmp(argv[1], "install") == 0) {
    if (argc < 3) {
      error("install <package>");
      return EINVAL;
    }
    
    Command::Install::run(argv[2], parseFlags(argc, argv, 3));
    return EXIT_SUCCESS;
  }
  if (strcmp(argv[1], "publish") == 0) {
    if (argc < 3) {
      error("publish <package>");
      return EINVAL;
    }
    
    Command::Publish::run(argv[2], parseFlags(argc, argv, 3));
    return EXIT_SUCCESS;
  }

  error();
  return EINVAL;
}