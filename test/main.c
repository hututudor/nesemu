#include <stdio.h>

#include "suites/bus.h"
#include "suites/mapper_0.h"
#include "suites/rom.h"

int main() {
  suite_bus();
  suite_rom();
  suite_mapper_0();
}