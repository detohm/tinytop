#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

class System {
 public:
  double MemUtilization();
  double CpuUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcess();
  std::string Kernel();
  std::string OperatingSystem();
};

#endif