#include <iostream>
#include <vector>

#include "linux.h"
#include "process.h"
#include "system.h"

int main() {
  std::cout << "Hello from TinyTop" << std::endl;

  LinuxHelper linux;
  std::vector<Process> ps = linux.ProcessList();
  for (auto a : ps) {
    std::cout << a.Pid << std::endl;
  }

  return 0;
}