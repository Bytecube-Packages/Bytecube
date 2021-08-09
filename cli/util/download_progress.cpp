#pragma once

#include "./exec.cpp"
using namespace std;

namespace Util {
  void download_progress(const char* args, void (*progress)(int)) {
    (*progress)(0);

    string cmd = string("curl ") + args;

    auto pipe = getPointer(cmd);
    if (!pipe) throw runtime_error("popen() failed!");

    bool str = true;
    bool new_line = true;
    int p = 0;
    
    array<char, 32> buffer;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
      string current = buffer.data();
      cout << current << flush;

      for (int i = 0; i < current.size(); i++) {
        char c = current[i];

        if (int(c) == 13) {
          //(*progress)(p);

          new_line = true;
          str = true;
          p = 0;
          continue;
        }

        if (!new_line) continue;

        if (c == ' ' && str) continue;
        if (c == ' ') new_line = false;

        if (isdigit(c)) {
          str = false;
          p = p * 10 + int(c) - '0';
        }
      }
    }

    (*progress)(100);
  }
}