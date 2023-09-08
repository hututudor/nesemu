#pragma once

#include "../../src/cpu/cpu.h"
#include "./bus.h"

cpu_t* mock_cpu() {
  bus_t* bus = mock_bus();
  return cpu_create(bus);
}