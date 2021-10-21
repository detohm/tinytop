#include "process.h"

Process::Process(OperatingSystem& os, int id) : pId_(id), os_(os) {}

int Process::PId() { return pId_; }
int Process::UId() { return os_.UId(pId_); }
double Process::CpuUsage() { return os_.CpuUsage(pId_); }
double Process::MemUsage() { return os_.MemUsage(pId_); }
std::string Process::Command() { return os_.Command(pId_); }
long Process::UpTime() { return os_.UpTime(pId_); }
