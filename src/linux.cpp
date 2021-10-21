#include "linux.h"

#include <dirent.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

std::vector<int> LinuxOS::ProcessIds() {
  std::vector<int> pids;
  DIR* directory = opendir("/proc/");
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      std::string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        pids.emplace_back(stoi(filename));
      }
    }
  }
  closedir(directory);
  return pids;
}
