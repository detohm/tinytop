#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "os.h"
#include "process.h"
class System {
 public:
  System(OperatingSystem& os);

  std::string OSName();
  double MemUtilization();
  double CpuUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcess();
  std::vector<Process>& Processes();

 private:
  OperatingSystem& os_;
  std::vector<Process> processes_ = {};
};

#endif