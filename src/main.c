#include <stdio.h>
#include <string.h>

#include <main.h>
#include <utils/arguments.h>
#include <utils/terminal.h>
#include <utils/asciiart.h>
#include <system/hardware/CPU/cpu.h>
#include <system/hardware/CPU/microarch.h>
#include <system/hardware/CPU/specifications.h>

/// @brief Spec Seek Entry Point
/// @param argc argument count
/// @param argv argument vector
int main(int argc, const char** argv){
    if (construct_arguments(argc, argv) != 0) return -1;
    if (!get_arguments().no_ansi) CLEAR_SCREEN();

    ASCII_DIVIDER("Spec Seek by Mellurboo", BLUE);
    printf("%sCompiled with GCC Version %d.%d.%d\n", BLUE,__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("%sCompiled at: %s : %s\n", BLUE, __DATE__, __TIME__);

    cpu_info(init_cpu());

    // Windows will close straight away after execution so this allows users to read it.
    #ifdef __MINGW32__
    printf("\n%sSpec Seek has finished, Press any key to exit: ", BWHITE);
    getchar();
    #endif

    printf("%s", RESET);
    fflush(stdout);
}

/// @brief Print and Display the CPU information
/// @param cpu populated cpu structure
void cpu_info(cpu_t cpu){
    IF_VENDOR_AMD({
        ASCII_DIVIDER("Processor", BRED);
        printf("%sName:      %s%s\n", BWHITE, RED, cpu.name);
        printf("%sMicroarch: %s%s\n", BWHITE, RED, amd_cpu_get_microarch(cpu.family, cpu.model, cpu.ext_model));
        printf("%sVendor:    %s%s\n", BWHITE, RED, cpu.vendor);
        ASCII_DIVIDER_SMALL("Identifiers", BRED);
        printf("%sModel: %s0x%X:\n", BWHITE, RED, cpu.model);
        printf("  %sBase Model: %s0x%X\n", BWHITE, RED, cpu.base_model);
        printf("  %sExt. Model: %s0x%X\n", BWHITE, RED, cpu.ext_model);
        printf("%sFamily:\t%s0x%X:\n", BWHITE, RED, cpu.family);
        printf("  %sBase Family: %s0x%X\n", BWHITE, RED, cpu.base_family);
        printf("  %sExt. Family: %s0x%X\n", BWHITE, RED, cpu.ext_family);
        printf("%sRevision: %s0x%X", BWHITE, RED, cpu.revision);
        ASCII_DIVIDER_SMALL("Specifications", BRED);
        printf("%sLogical Processors: %s%u\n", BWHITE, RED, cpu.logical_processors);
        printf("  %sPhysical Cores: %s%u\n", BWHITE, RED, cpu.physical_processors);
        printf("  %sThreads PerCore: %s%u\n", BWHITE, RED, cpu.threads_per_core);
    });

    IF_VENDOR_INTEL({
        ASCII_DIVIDER("Processor", BCYAN);
        printf("%sName:      %s%s\n", BWHITE, CYAN, cpu.name);
        printf("%sMicroarch: %s%s\n", BWHITE, CYAN, intel_get_cpu_microarch(cpu.family, cpu.base_model, cpu.ext_model, cpu.revision));
        printf("%sVendor:    %s%s\n", BWHITE, CYAN, cpu.vendor);
        ASCII_DIVIDER_SMALL("Identifiers", BCYAN);
        printf("%sModel: %s0x%X:\n", BWHITE, CYAN, cpu.model);
        printf("  %sBase Model: %s0x%X\n", BWHITE, CYAN, cpu.base_model);
        printf("  %sExt. Model: %s0x%X\n", BWHITE, CYAN, cpu.ext_model);
        printf("%sFamily:\t%s0x%X:\n", BWHITE, CYAN, cpu.family);
        printf("  %sBase Family: %s0x%X\n", BWHITE, CYAN, cpu.base_family);
        printf("  %sExt. Family: %s0x%X\n", BWHITE, CYAN, cpu.ext_family);
        printf("%sRevision: %s0x%X", BWHITE, CYAN, cpu.revision);
        ASCII_DIVIDER_SMALL_NOTEXT(BCYAN);
    });

    /*
        Printing the CPU features (Platform Specific logic is handled within the functions below.)
    */
    ASCII_DIVIDER("CPU Standard Features", BYELLOW);
    cpu_check_standard_features();
    ASCII_DIVIDER("CPU Extended Features", BYELLOW);
    cpu_check_extended_features();
    printf("\n");
}