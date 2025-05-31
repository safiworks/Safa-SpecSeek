#include <string.h>

#include <stdio.h>

#include "cpu.h"
#include "cpuid.h"
#include "../../../utils/arguments.h"
#include "../../../utils/terminal.h"

/// @brief Build the CPU information by populating a cpu_t struct
/// @return cpu_t CPU info structure.
cpu_t init_cpu(){
    //Construct
    cpu_t cpu;
    cpu.name = cpu_get_name();
    cpu.vendor = cpu_get_vendor();

    //Return Value
    return cpu;
}

/// @brief Also known as the CPU Brand String
/// @return CPU Name e.g. Ryzen 5 9600x 6 Core Processor
const char* cpu_get_name(){
    static char cpu_brand_string[49];           // [CPU_BRAND]
    unsigned int chunks[12];

    for (int i = 0; i < 3; i++){
        unsigned int eax, ebx, ecx, edx;
        cpuid(0x80000002 + i, 0, &eax, &ebx, &ecx, &edx);

        IF_VERBOSE(3){ PRINT_REGISTER_VALUES() }

        chunks[i * 4 + 0] = eax;
        chunks[i * 4 + 1] = ebx;
        chunks[i * 4 + 2] = ecx;
        chunks[i * 4 + 3] = edx;
    }

    memcpy(cpu_brand_string, chunks, sizeof(chunks));
    cpu_brand_string[48] = '\0';
    return cpu_brand_string;

}

/// @brief uses the CPUID function to return a text buffer containing the CPU Vendor
/// @return character array
const char* cpu_get_vendor(){
    //CPUID and Text Buffers
    static char vendor_string[13];              // [VENDOR_STRING (12bytes)] + [NT(1byte)]
    unsigned int eax, ebx, ecx, edx;
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    IF_VERBOSE(3){ PRINT_REGISTER_VALUES() }

    //Build the Vendor String + null terminator
    memcpy(vendor_string + 0, &ebx, 4);
    memcpy(vendor_string + 4, &edx, 4);
    memcpy(vendor_string + 8, &ecx, 4);
    vendor_string[12] = '\0';

    return vendor_string;
}