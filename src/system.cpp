#include "system.h"

#include <sys/utsname.h>

#include <string>

System::System(OperatingSystem& os) : os_(os){};

std::string System::OSName() {
  struct utsname unameData;
  uname(&unameData);
  return std::string(unameData.sysname) + " " + std::string(unameData.release);
}

double System::CpuUtilization() { return os_.CpuUtilization(); }
double System::MemUtilization() { return os_.MemUtilization(); }
long System::UpTime() { return os_.UpTime(); }
int System::TotalProcesses() { return os_.TotalProcesses(); }
int System::RunningProcess() { return os_.RunningProcess(); }

std::vector<Process>& System::Processes() {
  processes_.clear();
  std::vector<int> pids = os_.ProcessIds();
  for (int id : pids) {
    Process p(os_, id);
    processes_.emplace_back(p);
  }

  return processes_;
}