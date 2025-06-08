#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <utils/terminal.h>
#include <stdio.h>

unsigned int intel_cpu_get_threads_per_core() {
    if (max_supported_extended_leaf() < 0x0000001F) printf("%sIntel 0x0000001F not Supported, Core and Thread Info innacurate", BRED);

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 0, &eax, &ebx, &ecx, &edx);
    unsigned int level_type = (ecx >> 8) & 0xFF;

    // on the core make sure its a thread (SMT) if it is we can return its value
    if (level_type == 1 && ebx > 0){
        return ebx;
    }
    else{
        printf("%s%s:%d Fell out of level_type and ebx check, returning 0", BRED, __FILE__, __LINE__);
        return 0;
    }
}

unsigned int intel_cpu_get_logical_processor_count() {
    if (max_supported_extended_leaf() < 0x0000001F) printf("%sIntel 0x0000001F not Supported, Core and Thread Info innacurate", BRED);
    
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 1, &eax, &ebx, &ecx, &edx);
    unsigned int level_type = (ecx >> 8) & 0xFF;

    // on the core make sure its a core if it is we can return its value
    if (level_type == 2 && ebx > 0){
        return ebx;
    }
    else{
        printf("%s%s:%d Fell out of level_type and ebx check, returning 0", BRED, __FILE__, __LINE__);
        return 0;
    }
}

unsigned int intel_cpu_get_physical_core_count() {
    unsigned int logical = intel_cpu_get_logical_processor_count();
    unsigned int threads = intel_cpu_get_threads_per_core();

    if (threads == 0) threads = 1;

    return (threads > 0 && logical > 0) ? (logical / threads) : 0;
}