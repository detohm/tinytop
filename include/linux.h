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

  int UId(int pId);
  double CpuUsage(int pId);
  double MemUsage(int pId);
  long UpTime(int pId);
  std::string Command(int pId);
};

#endif