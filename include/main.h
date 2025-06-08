#ifndef _MAIN_H
#define _MAIN_H     1

#include <system/hardware/CPU/cpu.h>

#define VENDOR_COLOUR (strcmp(cpu_get_vendor(), _AMD_VENDOR_STRING) == 0 ? RED : CYAN)
#define BOLD_VENDOR_COLOUR (strcmp(cpu_get_vendor(), _AMD_VENDOR_STRING) == 0 ? BRED : BCYAN)

/// @brief Print and Display the CPU information
/// @param cpu populated cpu structure
void cpu_info(cpu_t cpu);

#endif