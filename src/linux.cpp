#include "linux.h"

#include <dirent.h>
#include <unistd.h>

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

long LinuxOS::UpTime() {
  std::string value;
  std::string line;
  std::ifstream filestream("/proc/uptime");
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value;

    return std::stol(value);
  }
  return 0;
}

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
    if (file->d_type == DT_DIR) {
      std::string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        pids.emplace_back(stoi(filename));
      }
    }
  }
  closedir(directory);
  return pids;
}

int LinuxOS::UId(int pId) {
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/status");
  std::string key;
  std::string value;
  std::string line;

  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        return std::stoi(value);
      }
    }
  }

  return -1;  // TODO - improve this is bad exception case.
}

double LinuxOS::CpuUsage(int pId) { return 0.0; }

double LinuxOS::MemUsage(int pId) {
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/status");
  std::string key;
  std::string value;
  std::string line;

  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        return stod(value) / 1024.0;
      }
    }
  }

  return -1;
}

long LinuxOS::UpTime(int pId) {
  std::string value;
  std::vector<std::string> values;
  std::string line;
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/stat");
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      values.push_back(value);
    }
    return (stol(values[21]) / sysconf(_SC_CLK_TCK));
  }

  return 0;
}

std::string LinuxOS::Command(int pId) {
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/cmdline");
  std::string command = "";

  if (filestream.is_open()) {
    getline(filestream, command);
  }

  return command;
}
