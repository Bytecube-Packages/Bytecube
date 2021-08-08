#pragma once

#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

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

string exec(string cmd) {
  return exec(cmd.c_str());
}