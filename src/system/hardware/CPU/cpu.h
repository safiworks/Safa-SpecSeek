#ifndef _CPU_H
#define _CPU_H  1

#define _AMD_VENDOR_STRING     "AuthenticAMD"
#define _INTEL_VENDOR_STRING   "GenuineIntel"

#define HAS_FEATURE(reg, bit) (((reg) & (1 << (bit))) != 0)

#define IF_VENDOR_AMD(amd_arch_code) \
    do { if (!memcmp(cpu_get_vendor(), _AMD_VENDOR_STRING, (unsigned long)12)) { amd_arch_code } } while (0)
#define IF_VENDOR_INTEL(intel_arch_code) \
    do { if (!memcmp(cpu_get_vendor(), _INTEL_VENDOR_STRING, (unsigned long)12)) { intel_arch_code } } while (0)

/// @brief CPU Structure
typedef struct cpu
{
    const char* name;
    const char* vendor;
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

#endif