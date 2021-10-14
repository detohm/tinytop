#include <unistd.h>

#include <iostream>
#include <vector>

#include "display.h"
#include "linux.h"
#include "process.h"
#include "system.h"

int main() {
  System sys;
  Display display(sys);
  display.Render();

  // LinuxHelper linux;
  // std::vector<Process> ps = linux.ProcessList();
  // for (auto a : ps) {
  //   std::cout << a.Pid << std::endl;
  // }

  return 0;
}