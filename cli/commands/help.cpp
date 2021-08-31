#include <iostream>
#include <string>

#include "../util/colors.cpp"
#include "../util/package.cpp"
using namespace std;

namespace Command {
  class Help {
    public:
      static void run() {
        string message = 
"Bytecube Version 1.0.0 \n"
" \n"
"USAGE: \n"
"bytecube <action> \n"
" \n"
"FLAGS: \n"
   "    --help      Prints help information \n"
   "    --version   Prints version information \n"
" \n"
"ACTIONS: \n"
  "    login <token>            Logs you in from the command line \n"
  "    install <package>        Install a package \n"
  "    publish <package>        Publish a package prompt \n"
" \n"
"ARGS: \n"
    "    <action>         The type of action performed \n";

        cout << message << endl;;
      }
  };
}