#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "os.h"
class Process {
 public:
  Process(OperatingSystem* os, int id);
  // Process(const Process& other);
  // Process(Process&& other);
  // Process& operator=(const Process& other);
  // Process& operator=(Process&& other);

  int PId();
  int UId();
  double CpuUsage() const;
  double MemUsage() const;
  std::string Command();
  long UpTime();

  bool operator<(Process const& a) const;

 private:
  int pId_;
  OperatingSystem* os_;
};

#endif