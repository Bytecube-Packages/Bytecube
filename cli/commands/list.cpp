#include <iostream>
#include <string>
#include <vector>

#include "../util/colors.cpp"
#include "../util/package.cpp"
#include "../util/json.cpp"

using namespace std;

namespace Command {
  class List {
    public:
      static void run() {
        string cmd  = "curl -s " + api + "/package/list";
        string result = exec(cmd.c_str());

        Json json = Json::parse(result);
        vector<Json> packages = json.getArray();

        for (int i = 0; i < packages.size(); i++) {
          set_bold(true);
          set_color(accent);
          string name = packages[i].getMap()["name"].getValue("");

          cout << name << endl;
        }
      }
  };
}