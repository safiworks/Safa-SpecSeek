#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/specifications.h>
#include <stdio.h>

unsigned int amd_cpu_get_physical_core_count(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);
    
    unsigned int logical_processor_count = amd_cpu_get_logical_processor_count();
    unsigned int core_per_thread = amd_cpu_get_thread_per_core();
    return logical_processor_count / core_per_thread;
}

unsigned int amd_cpu_get_thread_per_core(){
    unsigned int eax, ebx, ecx, edx;

    cpuid(0x8000001E, 0, &eax, &ebx, &ecx, &edx);
    unsigned int tpcu = (ebx >> 8) & 0xFF;
    return tpcu + 1;
}

unsigned int amd_cpu_get_logical_processor_count(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0 , &eax, &ebx, &ecx, &edx);

    return (ebx >> 16) & 0xFF;
}