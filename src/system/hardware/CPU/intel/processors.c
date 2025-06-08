#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <utils/terminal.h>
#include <stdio.h>

/// @brief INTEL ONLY gets all logical processors
/// @return int threads
unsigned int intel_cpu_get_physical_core_count(){
    return(intel_cpu_get_threads_per_core() > 0) ? 
        (amd_cpu_get_logical_processor_count() / intel_cpu_get_threads_per_core()) : 1;
}

unsigned int intel_cpu_get_threads_per_core(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 0, &eax, &ebx, &ecx, &edx);

    if (max_supported_leaf() < 0x0B) return -1;
    if (((ecx >> 8) & 0xFF) == 1 && ebx != 0) return ebx;
    

    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (ebx >> 16) & 0xFF;
}

unsigned int intel_cpu_get_logical_processor_count(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 1, &eax, &ebx, &ecx, &edx);

    if (((ecx >> 8) & 0xFF) == 1 && ebx != 0) return ebx;
    return 1;
}