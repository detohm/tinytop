#ifndef LINUX_OS_H
#define LINUX_OS_H

#include <vector>

#include "os.h"
#include "process.h"

class LinuxOS : public OperatingSystem {
 public:
  double MemUtilization();
  double CpuUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcess();
  std::vector<int> ProcessIds();
};

#endif