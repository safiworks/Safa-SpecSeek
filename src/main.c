#include <stdio.h>
#include <string.h>

#include "main.h"
#include "utils/arguments.h"
#include "utils/asciiart.h"
#include "utils/terminal.h"
#include "system/hardware/CPU/cpu.h"

/// @brief Spec Seek Entry Point
/// @param argc argument count
/// @param argv argument vector
int main(int argc, const char** argv){
    construct_arguments(argc, argv);

    CLEAR_SCREEN();
    ASCII_DIVIDER("Spec Seek by Mellurboo", BLUE);
    printf("%sCompiled with GCC Version %d.%d.%d\n", BLUE,__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("%sCompiled at: %s : %s\n", BLUE, __DATE__, __TIME__);
    if (arguments.verbose != 0) printf("%sRunning in Verbose Mode {%d}\n", BLUE, arguments.verbose);

    cpu_info(init_cpu());

    // Windows will close straight away after execution so this allows users to read it.
    #ifdef __MINGW32__
    printf("\n%sSpec Seek has finished, Press any key to exit: ", BWHITE);
    getchar();
    #endif
}

/// @brief Print and Display the CPU information
/// @param cpu populated cpu structure
void cpu_info(cpu_t cpu){
    IF_VENDOR_AMD({
        ASCII_DIVIDER("AMD CPU", RED);
        printf("%sCPU Name:\t%s%s\n", BWHITE, RED, cpu.name);
        printf("%sVendor String:\t%s%s\n", BWHITE, RED, cpu.vendor);

        ASCII_DIVIDER_SMALL("OEM Info", RED);
        printf("%sCPU Model:\t%s0x%X \t(%u)\n", BWHITE, RED, cpu.model, cpu.model);
        printf("%sCPU Family:\t%s0x%X \t(%u)\n", BWHITE, RED, cpu.family, cpu.family);
        printf("%sCPU Revision:\t%s0x%X \t(%u)", BWHITE, RED, cpu.revision, cpu.revision);
        ASCII_DIVIDER_SMALL_NOTEXT(RED);
    });

    IF_VENDOR_INTEL({
        ASCII_DIVIDER("INTEL CPU", CYAN);
        printf("%sCPU Name:\t%s%s\n", BWHITE, CYAN, cpu.name);
        printf("%sVendor String:\t%s%s\n", BWHITE, CYAN, cpu.vendor);

        ASCII_DIVIDER_SMALL("OEM Info", CYAN);
        printf("%sCPU Model:\t%s0x%X \t(%u)\n", BWHITE, CYAN, cpu.model, cpu.model);
        printf("%sCPU Family:\t%s0x%X \t(%u)\n", BWHITE, CYAN, cpu.family, cpu.family);
        printf("%sCPU Revision:\t%s0x%X \t(%u)", BWHITE, CYAN, cpu.revision, cpu.revision);
        ASCII_DIVIDER_SMALL_NOTEXT(CYAN);
    });

    ASCII_DIVIDER("CPU Standard Features", BYELLOW);
    cpu_check_standard_features();
    ASCII_DIVIDER("CPU Extended Features", BYELLOW);
    cpu_check_extended_features();
    printf("\n");
}