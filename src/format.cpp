#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

std::string Format::ElapsedTime(long seconds) {
  std::ostringstream oss;

  long hour = seconds / 3600;
  long minute = (seconds % 3600) / 60;
  long second = (seconds % 3600) % 60;

  oss << std::setfill('0') << std::setw(2) << hour << ":";
  oss << std::setfill('0') << std::setw(2) << minute << ":";
  oss << std::setfill('0') << std::setw(2) << second;

  return oss.str();
}
