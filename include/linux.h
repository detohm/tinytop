#ifndef LINUXHELPER_H
#define LINUXHELPER_H

#include <vector>

#include "process.h"

class LinuxHelper {
 public:
  std::vector<Process> ProcessList();
};

#endif