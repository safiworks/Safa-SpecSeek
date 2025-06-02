#include <stdio.h>

#include "cpu.h"
#include "cpuid.h"

#include "../../../utils/arguments.h"
#include "../../../utils/terminal.h"

#define FEATURES_PER_LINE   4

/// @brief prints the CPU features name and its support status given the current machine
/// @param verbosity how verbose the user must be to have the feature printed
/// @param status supported or not
/// @param feature_name feature name
void cpu_print_feature(int verbosity, int status, const char* feature_name){
    IF_VERBOSE(verbosity){
        static int feature_count;
        feature_count++;

        printf("%s%s: %s%s%s;\t\t", BWHITE,feature_name, status != 0 ? GREEN : RED, status != 0 ? "TRUE" : "FALSE", RESET);
        if (arguments.put_features_on_newline || feature_count % FEATURES_PER_LINE == 0) { printf("\n"); }
    }
}

/// @brief runs through features based on the Arch
void cpu_check_standard_features(){
    unsigned int eax, ebx, ecx, edx;

    IF_VENDOR_AMD({
        cpuid(1, 0, &eax, &ebx, &ecx, &edx);

        /*
            ECX Register Feature Bits
        */
        cpu_print_feature(0, HAS_FEATURE(ecx, 0), "SSE3");
        cpu_print_feature(1, HAS_FEATURE(ecx, 1), "PCLMUL");
        cpu_print_feature(1, HAS_FEATURE(ecx, 3), "MONITOR");
        cpu_print_feature(0, HAS_FEATURE(ecx, 9), "SSSE3");
        cpu_print_feature(0, HAS_FEATURE(ecx, 12), "FMA");
        cpu_print_feature(1, HAS_FEATURE(ecx, 13), "CMCH16B");
        cpu_print_feature(0, HAS_FEATURE(ecx, 19), "SSE4.1");
        cpu_print_feature(0, HAS_FEATURE(ecx, 20), "SSE4.2");
        cpu_print_feature(0, HAS_FEATURE(ecx, 21), "X2APIC");
        cpu_print_feature(1, HAS_FEATURE(ecx, 22), "MOVEBE");
        cpu_print_feature(0, HAS_FEATURE(ecx, 23), "POPCNT");
        cpu_print_feature(0, HAS_FEATURE(ecx, 25), "AES");
        cpu_print_feature(2, HAS_FEATURE(ecx, 26), "XSAVE");
        cpu_print_feature(2, HAS_FEATURE(ecx, 27), "OSXSAVE");
        cpu_print_feature(0, HAS_FEATURE(ecx, 28), "AVX");
        cpu_print_feature(2, HAS_FEATURE(ecx, 29), "F16C");
        cpu_print_feature(2, HAS_FEATURE(ecx, 30), "RDRAND");

        /*
            EDX Register Feature Bits
        */
        cpu_print_feature(1, HAS_FEATURE(edx, 0), "FPU");
        cpu_print_feature(0, HAS_FEATURE(edx, 1), "VME");
        cpu_print_feature(2, HAS_FEATURE(edx, 2), "DE");
        cpu_print_feature(1, HAS_FEATURE(edx, 3), "PSE");
        cpu_print_feature(2, HAS_FEATURE(edx, 4), "TSC");
        cpu_print_feature(1, HAS_FEATURE(edx, 5), "MSR");
        cpu_print_feature(0, HAS_FEATURE(edx, 6), "PAE");
        cpu_print_feature(1, HAS_FEATURE(edx, 7), "MCE");
        cpu_print_feature(2, HAS_FEATURE(edx, 8), "CPCH8B");
        cpu_print_feature(1, HAS_FEATURE(edx, 9), "APIC");
        cpu_print_feature(2, HAS_FEATURE(edx, 11), "SysEntSysEx");
        cpu_print_feature(1, HAS_FEATURE(edx, 12), "MTRR");
        cpu_print_feature(0, HAS_FEATURE(edx, 13), "PGE");
        cpu_print_feature(1, HAS_FEATURE(edx, 14), "MCA");
        cpu_print_feature(2, HAS_FEATURE(edx, 15), "CMOV");
        cpu_print_feature(1, HAS_FEATURE(edx, 16), "PAT");
        cpu_print_feature(2, HAS_FEATURE(edx, 17), "PSE36");
        cpu_print_feature(1, HAS_FEATURE(edx, 19), "CFLUSH");
        cpu_print_feature(0, HAS_FEATURE(edx, 23), "MMX");
        cpu_print_feature(2, HAS_FEATURE(ecx, 24), "FXSR");
        cpu_print_feature(0, HAS_FEATURE(ecx, 25), "SSE");
        cpu_print_feature(0, HAS_FEATURE(ecx, 26), "SSE2");
        cpu_print_feature(0, HAS_FEATURE(ecx, 28), "HTT");
    });
}

/// @brief gets the extended features from the CPUID (leaf 7 for AMD)
void cpu_check_extended_features(){
    unsigned int eax, ebx, ecx, edx;
    IF_VENDOR_AMD({
        /*
            EBX Register Feature Bits (0x00000007)
        */
        cpuid(0x00000007, 0, &eax, &ebx, &ecx, &edx);
        cpu_print_feature(1, HAS_FEATURE(ebx, 0), "FSGSBASE");
        cpu_print_feature(1, HAS_FEATURE(ebx, 3), "BMI1");
        cpu_print_feature(1, HAS_FEATURE(ebx, 5), "AVX2");
        cpu_print_feature(1, HAS_FEATURE(ebx, 7), "SMEP");
        cpu_print_feature(0, HAS_FEATURE(ebx, 8), "BMI2");
        cpu_print_feature(2, HAS_FEATURE(ebx, 10), "INVPCID");
        cpu_print_feature(2, HAS_FEATURE(ebx, 12), "PQM");
        cpu_print_feature(2, HAS_FEATURE(ebx, 15), "PQE");
        cpu_print_feature(2, HAS_FEATURE(ebx, 18), "RDSEED");
        cpu_print_feature(2, HAS_FEATURE(ebx, 19), "ADX");
        cpu_print_feature(1, HAS_FEATURE(ebx, 20), "SMAP");
        cpu_print_feature(2, HAS_FEATURE(ebx, 23), "CLFLUSHOPT");
        cpu_print_feature(2, HAS_FEATURE(ebx, 24), "CLWB");
        cpu_print_feature(0, HAS_FEATURE(ebx, 29), "SHA");

        /*
            ECX Register Feature Bits (0x00000007)
        */
        cpu_print_feature(2, HAS_FEATURE(ebx, 2), "UMIP");
        cpu_print_feature(2, HAS_FEATURE(ebx, 3), "PKU");
        cpu_print_feature(2, HAS_FEATURE(ebx, 4), "OSPKE");
        cpu_print_feature(2, HAS_FEATURE(ebx, 7), "CETSS");
        cpu_print_feature(1, HAS_FEATURE(ebx, 9), "VAES");
        cpu_print_feature(2, HAS_FEATURE(ebx, 10), "VPCMUL");
        cpu_print_feature(0, HAS_FEATURE(ebx, 16), "LA57");
        cpu_print_feature(1, HAS_FEATURE(ebx, 22), "RDPID");
        cpu_print_feature(2, HAS_FEATURE(ebx, 24), "BSLKTRP");
    });
}
