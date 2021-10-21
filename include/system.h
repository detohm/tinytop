#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

#include "os.h"

class System {
 public:
  System(OperatingSystem& os);

  std::string OSName();
  double MemUtilization();
  double CpuUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcess();

 private:
  OperatingSystem& os_;
};

#endif