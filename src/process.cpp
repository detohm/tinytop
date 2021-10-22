#include "process.h"

Process::Process(OperatingSystem* os, int id) : pId_(id), os_(os) {}

int Process::PId() { return pId_; }
int Process::UId() { return os_->UId(pId_); }
double Process::CpuUsage() const { return os_->CpuUsage(pId_); }
double Process::MemUsage() const { return os_->MemUsage(pId_); }
std::string Process::Command() { return os_->Command(pId_); }
long Process::UpTime() { return os_->UpTime(pId_); }

bool Process::operator<(Process const& a) const {
  return CpuUsage() > a.CpuUsage();
}
