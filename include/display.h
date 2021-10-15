#ifndef DISPLAY_H
#define DISPLAY_H
#include <curses.h>

#include "system.h"
class Display {
 public:
  Display(System& sys);
  void Render();

 private:
  System& system_;
  WINDOW* sysWindow_;
  WINDOW* processWindow_;
  void renderSystemWindow();
  void renderProcessWindow();
};

#endif