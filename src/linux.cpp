#include "linux.h"

#include <fstream>
#include <sstream>
#include <string>

#include "process.h"

std::vector<Process> LinuxOS::ProcessList() {
  // TODO - implement this
  std::vector<Process> v;
  return v;
}

double LinuxOS::CpuUtilization() {
  return 0.0;  // TODO - implement
}

double LinuxOS::MemUtilization() {
  std::string key = "";
  std::string value = "";
  float memTotal = 0.0;
  float memFree = 0.0;

  std::string line;
  std::ifstream filestream("/proc/meminfo");

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
        memTotal = stof(value);
        continue;
      }
      if (key == "MemFree:") {
        memFree = stof(value);
        break;
      }
    }
  }

  return (memTotal - memFree) / memTotal;
}

long LinuxOS::UpTime() { return 0; }
int LinuxOS::TotalProcesses() {
  std::string key;
  std::string value;
  std::string line;

  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
        return std::stoi(value);
      }
    }
  }
  return 0;
}
int LinuxOS::RunningProcess() {
  std::string key;
  std::string value;
  std::string line;

  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        return std::stoi(value);
      }
    }
  }
  return 0;
}
