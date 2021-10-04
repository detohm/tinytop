#include <ncurses.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "linux.h"
#include "process.h"
#include "system.h"
int main() {
  // init ncurse
  initscr();
  cbreak();

  int row, col;
  getmaxyx(stdscr, row, col);

  refresh();

  WINDOW *win = newwin(row, col, 0, 0);
  box(win, 0, 0);
  wrefresh(win);
  refresh();

  getch();
  endwin();

  // LinuxHelper linux;
  // std::vector<Process> ps = linux.ProcessList();
  // for (auto a : ps) {
  //   std::cout << a.Pid << std::endl;
  // }

  return 0;
}