#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "os.h"
class Process {
 public:
  Process(OperatingSystem& os, int id);
  int PId();
  int UId();
  double CpuUsage();
  double MemUsage();
  std::string Command();
  long UpTime();

 private:
  int pId_;
  OperatingSystem& os_;
};

#endif