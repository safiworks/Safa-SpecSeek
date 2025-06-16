#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <utils/terminal.h>
#include <stdio.h>

/// @brief INTEL ONLY gets the amount of threads per CPU physical Core
/// @return threads per core
unsigned int intel_cpu_get_threads_per_core() {
    if (max_supported_extended_leaf() < 0x0000000B) printf("%sCPUID Leaf 0x0000000B not Supported, Core and Thread Info may be ommited\n", BRED);
    if (max_supported_extended_leaf() < 0x0000001F) printf("%sCPUID Leaf 0x0000001F not Supported, Core and Thread Info innacurate\n", BRED);

    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 0, &eax, &ebx, &ecx, &edx);
    unsigned int level_type = (ecx >> 8) & 0xFF;

    // on the core make sure its a thread (SMT) if it is we can return its value
    if (level_type == 1 && ebx > 0){
        return ebx;
    }
    else{
        printf("%s%s:%d Fell out of level_type and ebx check, returning 0\n", BRED, __FILE__, __LINE__);
        return 0;
    }
}

/// @brief INTEL ONLY Gets the logical processor count for the CPU Package
/// @return Logicial Processor Count
unsigned int intel_cpu_get_logical_processor_count() {
    if (max_supported_extended_leaf() < 0x0000000B) printf("%sCPUID Leaf 0x0000000B not Supported, Core and Thread Info may be ommited\n", BRED);
    if (max_supported_extended_leaf() < 0x0000001F) printf("%sCPUID Leaf 0x0000001F not Supported, Core and Thread Info innacurate\n", BRED);
    
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x0B, 1, &eax, &ebx, &ecx, &edx);
    unsigned int level_type = (ecx >> 8) & 0xFF;

    // on the core make sure its a core if it is we can return its value
    if (level_type == 2 && ebx > 0){
        return ebx;
    } else{
        printf("%s%s:%d Fell out of level_type and ebx check, returning 0\n", BRED, __FILE__, __LINE__);
        return 0;
    }
}

unsigned int intel_cpu_get_physical_core_count() {
    unsigned int logical = intel_cpu_get_logical_processor_count();
    unsigned int threads = intel_cpu_get_threads_per_core();

    if (threads == 0) threads = 1;

    return (threads > 0 && logical > 0) ? (logical / threads) : 0;
}

int get_physical_cores() {
#if defined(__x86_64__) || defined(__i386__)
    unsigned int eax, ebx, ecx, edx;
    // Leaf 0xB gives topology on modern Intel CPUs
    if (max_supported_leaf(0, NULL) >= 0xB) {
        int cores = 0;
        for (int level = 0; ; ++level) {
            cpuid(0xB, level, &eax, &ebx, &ecx, &edx);
            if ((ecx & 0xff00) >> 8 == 1) { // Level type 1 = core
                cores = ebx;
                break;
            }
            if (ebx == 0) break;
        }
        return cores > 0 ? cores : 1;
    }
    // Fallback: older AMD/Intel CPUs, use leaf 4
    else if (max_supported_leaf(0, NULL) >= 4) {
        cpuid(4, 0, &eax, &ebx, &ecx, &edx);
        int cores = ((eax >> 26) & 0x3f) + 1;
        return cores > 0 ? cores : 1;
    }
    // Fallback: 1 core
    return 1;
#else
    // For non-x86, fallback to 1 core
    return 1;
#endif
}