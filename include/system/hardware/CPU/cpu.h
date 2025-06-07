#ifndef _CPU_H
#define _CPU_H  1

#define _AMD_VENDOR_STRING     "AuthenticAMD"
#define _INTEL_VENDOR_STRING   "GenuineIntel"

#define HAS_FEATURE(reg, bit) (((reg) & (1 << (bit))) != 0)

#define IF_VENDOR_AMD(amd_arch_code) \
    do { if (!memcmp(cpu_get_vendor(), _AMD_VENDOR_STRING, (unsigned long)12)) { amd_arch_code } } while (0)
#define IF_VENDOR_INTEL(intel_arch_code) \
    do { if (!memcmp(cpu_get_vendor(), _INTEL_VENDOR_STRING, (unsigned long)12)) { intel_arch_code } } while (0)

#define PRINT_REGISTER_VALUES() printf("%s%s:%s():%d eax:0x%08X, ebx:0x%08X, ecx:0x%08X, edx:0x%08X\n", BMAGENTA, __FILE__, __PRETTY_FUNCTION__, __LINE__, (eax), (ebx), (ecx), (edx));

/// @brief CPU Structure
typedef struct cpu
{
    const char* name;
    const char* vendor;
    unsigned int model;
    unsigned int base_model;
    unsigned int ext_model;
    unsigned int family;
    unsigned int base_family;
    unsigned int ext_family;
    unsigned int revision;

    unsigned int logical_processors;
    unsigned int physical_processors;
    unsigned int threads_per_core;
}cpu_t;

/// @brief CPUID instruction wrapper that places results from the leaf and subleaf into respective locations
/// @param leaf CPUID Leaf (code)
/// @param subleaf CPUID Subleaf (int argument)
/// @param eax u32 contains part of CPUID results
/// @param ebx u32 contains part of CPUID results
/// @param ecx u32 contains part of CPUID results
/// @param edx u32 contains part of CPUID results
void cpuid(
    unsigned int leaf,
    unsigned int subleaf,
    unsigned int* eax,
    unsigned int* ebx,
    unsigned int* ecx,
    unsigned int* edx
);

/// @brief Constructs a CPU variable
/// @return cpu_t
cpu_t init_cpu();

/// @brief Uses the CPUID function to return a text buffer containing the CPU Vendor
/// @return character array
const char* cpu_get_vendor();

/// @brief Also known as the CPU Brand String
/// @return CPU Name e.g. Ryzen 5 9600x 6 Core Processor
const char* cpu_get_name();

/// @brief prints the CPU features name and its support status given the current machine
/// @param verbosity how verbose the user must be to have the feature printed
/// @param status supported or not
/// @param feature_name feature name
void cpu_print_feature(int verbosity, int status, const char* feature_name);

/// @brief runs through features based on the Arch
void cpu_check_standard_features();

/// @brief gets the extended features from the CPUID (leaf 7 for AMD)
void cpu_check_extended_features();

/// @brief get the CPU model ID leaf 1, 0
/// @return unsigned int
unsigned int cpu_get_base_model();

/// @brief Gets the extended model number of the CPU, this isnt really that useful
/// @return unsigned int full model
unsigned int cpu_get_extended_model();

/// @brief Returns the final "Display Model" based on CPUID
unsigned int cpu_get_full_model();

/// @brief Gets the CPU family ID combining extended and base family
/// @return unsigned int full family number
unsigned int cpu_get_family();

/// @brief gets only the base family from the CPU
/// @return base family int
unsigned int cpu_get_base_family();

/// @brief gets only the extended family from the CPU
/// @return extended family int
unsigned int cpu_get_extended_family();

/// @brief Gets the current CPU revision (stepping)
/// @return unsigned int stepping number
unsigned int cpu_get_revision();

/// @brief get the amount of logical processors on the CPU
/// @return int processors
unsigned int cpu_get_logical_processor_count();

#endif