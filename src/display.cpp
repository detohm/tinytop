#include "display.h"

#include <curses.h>

#include <chrono>
#include <string>
#include <thread>

#include "system.h"

const int processWindowRow = 10;

// Constructor
Display::Display(System& sys) : system_(sys) {}

void Display::Render() {
  initscr();
  noecho();
  cbreak();

  int xMax = getmaxx(stdscr);
  sysWindow_ = newwin(9, xMax, 0, 0);
  processWindow_ = newwin(processWindowRow + 1, xMax, getmaxy(sysWindow_), 0);

  while (true) {
    box(sysWindow_, 0, 0);
    renderSystemWindow();
    wrefresh(sysWindow_);

    box(processWindow_, 0, 0);
    renderProcessWindow();
    wrefresh(processWindow_);

    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  endwin();
}

void Display::renderSystemWindow() {
  int row = 0;
  mvwprintw(sysWindow_, ++row, 2, ("OS: " + system_.OSName()).c_str());
  mvwprintw(sysWindow_, ++row, 2, "CPU: ");
  mvwprintw(
      sysWindow_, ++row, 2,
      ("Mem: " + std::to_string(system_.MemUtilization() * 100.0)).c_str());
  mvwprintw(
      sysWindow_, ++row, 2,
      ("Process[total]: " + std::to_string(system_.TotalProcesses())).c_str());
  mvwprintw(sysWindow_, ++row, 2,
            ("Process[running]: " + std::to_string(system_.RunningProcess()))
                .c_str());
  mvwprintw(sysWindow_, ++row, 2,
            ("UpTime: " + std::to_string(system_.UpTime())).c_str());

  wrefresh(sysWindow_);
}

void Display::renderProcessWindow() {
  int row = 0;
  int col[6] = {2, 9, 16, 26, 38, 48};

  mvwprintw(processWindow_, ++row, col[0], "PID");
  mvwprintw(processWindow_, row, col[1], "User");
  mvwprintw(processWindow_, row, col[2], "CPU[%%]");
  mvwprintw(processWindow_, row, col[3], "Mem[MB]");
  mvwprintw(processWindow_, row, col[4], "Time");
  mvwprintw(processWindow_, row, col[5], "CMD");

  auto processes = system_.Processes();

  int rows = (processes.size() > processWindowRow) ? processWindowRow
                                                   : processes.size();
  for (int i = 0; i < rows; i++) {
    row++;
    mvwprintw(processWindow_, row, col[0],
              std::to_string(processes[i].PId()).c_str());
    mvwprintw(processWindow_, row, col[1], "");
    mvwprintw(processWindow_, row, col[2], "");
    mvwprintw(processWindow_, row, col[3], "");
    mvwprintw(processWindow_, row, col[4], "");
    mvwprintw(processWindow_, row, col[5], "");
  }

  wrefresh(processWindow_);
}
