#ifndef LINUX_OS_H
#define LINUX_OS_H

#include <vector>

#include "os.h"
#include "process.h"

class LinuxOS : public OperatingSystem {
 public:
  std::vector<Process> ProcessList();
  double MemUtilization();
  double CpuUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcess();
};

#endif