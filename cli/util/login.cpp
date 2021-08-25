#pragma once

#include <string>
#include "api.cpp"
#include "json.cpp"
#include "exec.cpp"
#include "os.cpp"
#include "colors.cpp"

namespace Util {
  namespace Login {
    static string get_token_file() {
      if (isMacos) return "~/.bytecube";
      if (isWindows) return "\"%userprofile%/.bytecube\"";
      return "";
    }
    static string get_token() {
      string file = Util::Login::get_token_file();
      string token = exec("cat " + file + " 2>&1");
      return token.substr(0, token.find("\n"));
    }
    static void set_token(string token) {
      string file = Util::Login::get_token_file();
      exec("echo " + token + " > " + file + " 2>&1");
    }
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
    static void print_name(string name) {
      cout << "Hello, ";

      set_color(accent);
      cout << name;

      reset();
      cout << "!" << endl;
    }
  }
}
