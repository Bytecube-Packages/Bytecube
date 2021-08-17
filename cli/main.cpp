#include <iostream>
#include <stdlib.h>
#include <string>
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

int main(int argc, char** argv) {
  reset();
  set_bold(true);
  if (argc < 2) {
    error();
    return EINVAL;
  }
  if (strcmp(argv[1], "login") == 0) {
    Command::Login::run();
    return EXIT_SUCCESS;
  }
  if (strcmp(argv[1], "install") == 0) {
    if (argc < 3) {
      error("install <package>");
      return EINVAL;
    }
    
    Command::Install::run(argv[2]);
    return EXIT_SUCCESS;
  }
  if (strcmp(argv[1], "publish") == 0) {
    if (argc < 3) {
      error("publish <package>");
      return EINVAL;
    }
    
    Command::Publish::run(argv[2]);
    return EXIT_SUCCESS;
  }

  error();
  return EINVAL;
}