#include "display.h"

#include <curses.h>

#include <chrono>
#include <string>
#include <thread>

#include "format.h"
#include "system.h"

const int processWindowRow = 10;

// Constructor
Display::Display(System& sys) : system_(sys) {}

void Display::Render() {
  initscr();
  noecho();
  cbreak();

  int xMax = getmaxx(stdscr);
  sysWindow_ = newwin(9, xMax - 1, 0, 0);
  processWindow_ =
      newwin(processWindowRow + 3, xMax - 1, getmaxy(sysWindow_), 0);

  while (true) {
    box(sysWindow_, 0, 0);
    box(processWindow_, 0, 0);
    renderSystemWindow();
    renderProcessWindow();
    refresh();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  endwin();
}

void Display::renderSystemWindow() {
  int row = 0;
  mvwprintw(sysWindow_, ++row, 2, ("OS: " + system_.OSName()).c_str());
  mvwprintw(
      sysWindow_, ++row, 2,
      ("CPU: " + std::to_string(system_.CpuUtilization() * 100.0)).c_str());
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
            ("UpTime: " + Format::ElapsedTime(system_.UpTime())).c_str());

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
    mvwprintw(processWindow_, row, col[1],
              (std::to_string(processes[i].UId())).c_str());
    mvwprintw(processWindow_, row, col[2],
              std::to_string(processes[i].CpuUsage() * 100).c_str());
    mvwprintw(processWindow_, row, col[3],
              std::to_string(processes[i].MemUsage()).c_str());
    mvwprintw(processWindow_, row, col[4],
              Format::ElapsedTime(processes[i].UpTime()).c_str());
    mvwprintw(processWindow_, row, col[5], processes[i].Command().c_str());
  }

  wrefresh(processWindow_);
}
