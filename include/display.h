#ifndef DISPLAY_H
#define DISPLAY_H
#include "system.h"

class Display {
 public:
  Display(System& sys);
  void Render();

 private:
  System& system_;
};

#endif