#include <iostream>
#include <set>
#include <string>

#include "../util/login.cpp"
#include "../util/json.cpp"
#include "../util/api.cpp"
#include "../util/exec.cpp"
#include "../util/colors.cpp"

using namespace std;
using namespace Util;
using namespace Util::Login;

namespace Command {
  class Login {
    public:
      static void run(set<string> flags) {
        cout << "Input the token found at https://bytecube.tk/token" << endl;
        string access_token = input("Token");
        string name = login(access_token);
        print_name(name);

        set_token(access_token);
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