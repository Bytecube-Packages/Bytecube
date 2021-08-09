#pragma once

#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include <stdio.h>
#include <stdlib.h>

#include "./os.cpp"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
  unique_ptr<FILE, decltype(&_pclose)> getPointer(const char* cmd) {
    unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    return pipe;
  }
#else
  unique_ptr<FILE, decltype(&pclose)> getPointer(const char* cmd) {
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    return pipe;
  }
#endif

auto getPointer(string cmd) {
  return getPointer(cmd.c_str());
}

string exec(const char* cmd) {
  auto pipe = getPointer(cmd);
  if (!pipe) throw runtime_error("popen() failed!");

  string result;
  array<char, 128> buffer;
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) result += buffer.data();
  cout << "result: " << result << endl;
  return result;
}

string exec(string cmd) {
  return exec(cmd.c_str());
}