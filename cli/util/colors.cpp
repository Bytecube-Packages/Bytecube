#pragma once

#include <iostream>
using namespace std;

void set_color(int color) {
  cout << "\033[" << color << "m";
}
void set_bold(bool bold) {
  if (bold) {
    cout << "\033[1m";
  } else {
    cout << "\033[21m";
  }
}
void reset() {
  cout << "\033[0m";
}

int accent = 36;