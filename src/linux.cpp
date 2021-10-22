#include "linux.h"

#include <dirent.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> LinuxOS::parseCpuStat() {
  std::string line;
  std::string value;
  std::vector<std::string> strs;
  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value;  // cpu first column

    while (linestream >> value) {
      strs.push_back(value);
    }
  }
  return strs;
}

double LinuxOS::CpuUtilization() {
  std::vector<std::string> stats = parseCpuStat();
  long curActiveJiffies = 0;
  long curTotalJiffies = 0;
  for (unsigned int i = 0; i < stats.size(); i++) {
    curTotalJiffies += std::stol(stats[i]);
    if (i != 3 && i != 4) {
      curActiveJiffies += std::stol(stats[i]);
    }
  }

  long deltaActiveJiffies = curActiveJiffies - activeJiffies_;
  long deltaTotalJiffies = curTotalJiffies - totalJiffies_;
  activeJiffies_ = curActiveJiffies;
  totalJiffies_ = curTotalJiffies;

  return ((double)deltaActiveJiffies) / deltaTotalJiffies;
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

long LinuxOS::activeJiffies(int pId) {
  std::string line;
  std::string value;
  std::vector<std::string> values;
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/stat");
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      values.push_back(value);
    }

    return stol(values[13]) + stol(values[14]) + stol(values[15]) +
           stol(values[16]);
  }
  return 0;
}

double LinuxOS::CpuUsage(int pId) {
  std::vector<std::string> stats = parseCpuStat();
  long totalJiffies = 0;
  for (unsigned int i = 0; i < stats.size(); i++) {
    totalJiffies += std::stol(stats[i]);
  }
  long processActiveJiffies = activeJiffies(pId);

  return ((double)processActiveJiffies) / totalJiffies;
}

double LinuxOS::MemUsage(int pId) {
  std::ifstream filestream("/proc/" + std::to_string(pId) + "/status");
  std::string key;
  std::string value;
  std::string line;

  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      // if (key == "VmSize:") {
      if (key == "VmRSS:") {
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
