#ifndef TINYTOP_OS_H
#define TINYTOP_OS_H

#include <string>

class OperatingSystem {
 public:
  virtual double MemUtilization() = 0;
  virtual double CpuUtilization() = 0;
  virtual long UpTime() = 0;
  virtual int TotalProcesses() = 0;
  virtual int RunningProcess() = 0;
};

#endif