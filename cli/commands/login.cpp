#include <iostream>
#include <set>
#include <string>

#include "../util/json.cpp"
#include "../util/api.cpp"
#include "../util/exec.cpp"
#include "../util/colors.cpp"

using namespace std;
using namespace Util;

namespace Command {
  class Login {
    public:
      static void run(set<string> flags) {
        string access_token = input("Access Token");
        string name = login(access_token);

        string home = "~";
        if (isWindows) {
          home = "%userprofile%";
        }


        cout << "Hello, ";

        set_color(accent);
        cout << name;

        reset();
        cout << "!" << endl;

        exec("echo " + access_token + " > \"" + home + "/.bytecube\" 2>&1");
      }
    private:
      static string login(string access_token) {
        string cmd = "curl -s -k \"" + api + "/me\" -H \"Authorization: Bearer " + access_token + "\"";
        string result = exec(cmd.c_str());

        Json jsonResult = Json::parse(result);

        if (jsonResult.type != "object") {
          set_bold(true);
          set_color(31);
          cerr << "Error: Invalid Response" << endl;
          reset();

          exit(1);
        }

        string error = jsonResult.getMap()["error"].getValue("");
        if (error.length() > 0) {
          set_bold(true);
          set_color(31);
          cerr << "Error: " << error << endl;
          reset();

          exit(1);
        }

        string name = jsonResult.getMap()["name"].getValue("");
        return name;
      }
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