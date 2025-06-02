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
    unsigned int family;
    unsigned int revision;
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

/// @brief uses the CPUID function to return a text buffer containing the CPU Vendor
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

/// @brief Gets the model number of the CPU following the conditions
/// @return unsigned int
unsigned int cpu_get_model();

/// @brief gets the CPU family ID following the conditions
/// @return unsigned int
unsigned int cpu_get_family();

/// @brief gets the current CPU revision
/// @return unsigned int
unsigned int cpu_get_revision();

#endif