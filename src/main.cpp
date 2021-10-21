#include <unistd.h>

#include <iostream>
#include <vector>

#include "display.h"
#include "linux.h"
#include "process.h"
#include "system.h"

int main() {
  LinuxOS linuxOs;      // TODO - support multiple os
  System sys(linuxOs);  // Polymorphism of os
  Display display(sys);

  display.Render();

  return 0;
}