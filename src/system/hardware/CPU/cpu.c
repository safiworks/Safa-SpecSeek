#include <string.h>
#include <stdio.h>

#include "cpu.h"
#include "cpuid.h"
#include "../../../utils/arguments.h"
#include "../../../utils/terminal.h"

/*
    A lot of the code here is not archetecture specific, anything that is has been placed in {oem_name}/microarch.h 
    because really all that was vendor platform specific was the microarchetecutre nameing scheme and it was too large
    to realistically have here. 
*/


/// @brief Build the CPU information by populating a cpu_t struct
/// @return cpu_t CPU info structure.
cpu_t init_cpu(){
    // Construct
    cpu_t cpu;
    cpu.name = cpu_get_name();
    cpu.model = cpu_get_model();                    // this should be the model + the extended model as per AMD and Intel docs
    cpu.ext_model = cpu_get_extended_model();       // this is the extended model on its own
    cpu.family = cpu_get_family();
    cpu.vendor = cpu_get_vendor();                  // this MUST be accuratly populated or it falls apart at arch specific code
    cpu.revision = cpu_get_revision();

    // Return Value
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

/// @brief Uses the CPUID function to return a text buffer containing the CPU Vendor
/// @return character array
const char* cpu_get_vendor(){
    static char vendor_string[13];              // [VENDOR_STRING (12 bytes)] + [NT(1 byte)]
    unsigned int eax, ebx, ecx, edx;
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    IF_VERBOSE(3){ PRINT_REGISTER_VALUES() }

    memcpy(vendor_string + 0, &ebx, 4);
    memcpy(vendor_string + 4, &edx, 4);
    memcpy(vendor_string + 8, &ecx, 4);
    vendor_string[12] = '\0';

    return vendor_string;
}

/// @brief get the CPU model ID leaf 1, 0
/// @return unsigned int
unsigned int cpu_get_model() {
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    // Variables from CPUID
    unsigned int base_family = (eax >> 8) & 0xF;
    unsigned int ext_family = (eax >> 20) & 0xFF;
    unsigned int base_model = (eax >> 4) & 0xF;
    unsigned int ext_model = (eax >> 16) & 0xF;

    // construct the family value because we need it later
    // to get the model
    unsigned int family = base_family;
    if (base_family == 0xF) { family += ext_family; }

    // construct model, if the family is 6 or 0xF then we combine the
    // we shift the ext_model bits left and combine them with base_model
    // if the first condition isnt met then model is just the base model
    unsigned int model;
    if (family == 6 || family == 0xF) {
        model = (ext_model << 4) | base_model;
    } else {
        model = base_model;
    }

    return model;
}


/// @brief Gets the extended model number of the CPU, this isnt really that useful
/// @return unsigned int full model
unsigned int cpu_get_extended_model(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return (eax >> 16) & 0xF;  // Extended Model only (4 bits)
}

/// @brief Gets the CPU family ID combining extended and base family
/// @return unsigned int full family number
unsigned int cpu_get_family() {
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    unsigned int base_family = (eax >> 8) & 0xF;
    unsigned int ext_family = (eax >> 20) & 0xFF;

    if (base_family == 0xF) {
        return base_family + ext_family;
    } else {
        return base_family;
    }
}

/// @brief Gets the current CPU revision (stepping)
/// @return unsigned int stepping number
unsigned int cpu_get_revision(){
    unsigned int eax, ebx, ecx, edx;
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);
    return eax & 0xF;
}
