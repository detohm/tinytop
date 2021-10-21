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