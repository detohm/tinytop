#include "display.h"

#include <curses.h>

#include <chrono>
#include <thread>

#include "system.h"
// Constructor
Display::Display(System& sys) : system_(sys) {}

void Display::Render() {
  initscr();
  noecho();
  cbreak();

  int xMax = getmaxx(stdscr);
  WINDOW* sysWindow = newwin(9, xMax, 0, 0);

  while (true) {
    box(sysWindow, 0, 0);
    wrefresh(sysWindow);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  endwin();
}
