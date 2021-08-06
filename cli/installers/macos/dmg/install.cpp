#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

using namespace std;

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

string attach(const char* name) {
  string start = "hdiutil attach ";

  cout << "Attaching " << name << endl;

  string command = start + name;
  string volume = exec(command.c_str());

  string r = "\\/Volumes\\/(\\s?\\w+)*";
  smatch m;
  regex_search(volume, m, regex(r));
  
  return regex_replace(m.str(), regex("\\s"), "\\ ");
}

void copy(const char* name) {
  cout << "Installing " << endl;

  string start = "cp -rf ";
  string end = "/*.app /Applications";

  string command = start + name + end;
  exec(command.c_str());
}

void detach(const char* name) {
  string start = "hdiutil detach ";
  string command = start + name;

  cout << "Detaching " << name << endl;

  exec(command.c_str());
}

int main(int argc, char** argv) {
  if (argc < 2) return 1;
  
  string volume = attach(argv[1]);
  copy(volume.c_str());
  detach(volume.c_str());
}