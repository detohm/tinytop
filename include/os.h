#ifndef TINYTOP_OS_H
#define TINYTOP_OS_H

#include <string>
#include <vector>
class OperatingSystem {
 public:
  virtual double MemUtilization() = 0;
  virtual double CpuUtilization() = 0;
  virtual long UpTime() = 0;
  virtual int TotalProcesses() = 0;
  virtual int RunningProcess() = 0;
  virtual std::vector<int> ProcessIds() = 0;

  virtual int UId(int pId) = 0;
  virtual long UpTime(int pId) = 0;
  virtual double CpuUsage(int pId) = 0;
  virtual double MemUsage(int pId) = 0;
  virtual std::string Command(int pId) = 0;
};

#endif