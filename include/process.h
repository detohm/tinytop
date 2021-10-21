#ifndef PROCESS_H
#define PROCESS_H

#include <string>
class Process {
 public:
  Process(int id);
  int PId();
  int UId();
  double CpuUsage();
  double MemUsage();

 private:
  int pId_;
};

#endif