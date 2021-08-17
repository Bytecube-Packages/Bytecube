#pragma once

#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #include <iostream>
  using namespace std;

  int clear_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
  int current_color = clear_color;

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  void set_color(int color) {
    if (color == 0) {
      current_color = clear_color;
      SetConsoleTextAttribute(hConsole, current_color);

      return;
    }

    int new_color = 0;
    int multiplier = 1;

    if (color > 40) {
      multiplier = 16;
      color -= 10;
    }

    int mask = (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED) / multiplier;
    int mask_color = current_color & mask;

    if (color == 31) new_color = FOREGROUND_RED;
    if (color == 36) new_color = FOREGROUND_GREEN | FOREGROUND_BLUE;
    
    new_color *= multiplier;
    new_color |= mask_color;
    
    current_color = new_color;
    SetConsoleTextAttribute(hConsole, current_color);
  }
  void set_bold(bool bold) {
    if (bold) {
      current_color |= FOREGROUND_INTENSITY;
      SetConsoleTextAttribute(hConsole, current_color);
    } else {
      current_color &= ~FOREGROUND_INTENSITY;
      SetConsoleTextAttribute(hConsole, current_color);
    }
  }
  void reset() {
    current_color = clear_color;
    SetConsoleTextAttribute(hConsole, current_color);
  }

  int accent = 36;
#else
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
#endif