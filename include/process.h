#ifndef PROCESS_H
#define PROCESS_H

#include <string>
class Process {
 public:
  int Pid;
  int Uid;
  std::string User;
  double CpuUsage;
  double MemUsage;
  int Processor;
};

#endif