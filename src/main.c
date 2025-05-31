#include <stdio.h>
#include <string.h>

#include "main.h"
#include "utils/asciiart.h"
#include "utils/terminal.h"
#include "system/hardware/CPU/cpu.h"

/// @brief Spec Peek Entry Point
/// @param argc argument count
/// @param argv argument vector
int main(){
    CLEAR_SCREEN();
    ASCII_BANNER(BBLUE, "Spec Peek");
    printf("%sCompiled with GCC Version %d.%d.%d\n", BLUE,__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("%sCompiled at: %s : %s\n", BLUE, __DATE__, __TIME__);

    cpu_info(init_cpu());
}

/// @brief Print and Display the CPU information
/// @param cpu populated cpu structure
void cpu_info(cpu_t cpu){
    IF_VENDOR_AMD({
        ASCII_BANNER(RED, "   AMD CPU");
        printf("%sCPU Name:\t%s%s\n", BWHITE, RED, cpu.name);
        printf("%sVendor String:\t%s%s\n", BWHITE, RED, cpu.vendor);
    });

    IF_VENDOR_INTEL({
        ASCII_BANNER(CYAN, "INTEL PROCESSOR");
        printf("%sVendor String:\t%s%s\n", BWHITE, RED, cpu.vendor);
    });
}