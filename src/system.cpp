#include "system.h"

#include <sys/utsname.h>

#include <string>

std::string System::OperatingSystem() {
  struct utsname unameData;
  uname(&unameData);

  return std::string(unameData.sysname) + " " + std::string(unameData.release);
}