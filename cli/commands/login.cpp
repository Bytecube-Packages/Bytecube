#include <iostream>
#include "../util/colors.cpp"
using namespace std;

namespace Command {
  class Login {
    public:
      static void run() {
        cout << "Hello, ";

        set_color(accent);
        cout << "John";

        set_color(0);
        cout << "!" << endl;
      }
  };
}