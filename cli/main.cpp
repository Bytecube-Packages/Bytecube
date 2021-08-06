#include <iostream>
#include <string>
#include "./util/colors.cpp"

#include "./commands/login.cpp"
#include "./commands/add.cpp"
using namespace std;

void error() {
  set_color(31);
  cerr << "Usage: bytecube [login | install | publish]" << endl;
  set_color(0);
}
void error(string message) {
  set_color(31);
  cerr << "Usage: bytecube " << message << endl;
  set_color(0);
}

int main(int argc, char** argv) {
  set_color(0);
  set_color(1);
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

  error();
  return EINVAL;
}