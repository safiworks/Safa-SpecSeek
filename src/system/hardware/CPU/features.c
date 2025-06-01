#include <stdio.h>

#include "cpu.h"
#include "cpuid.h"
#include "../../../utils/arguments.h"
#include "../../../utils/terminal.h"

void cpu_print_feature(int status, const char* feature_name){
    if(status != 0){
        printf("%s%s %sTRUE", BWHITE, feature_name, GREEN);
    }else{
        printf("%s%s %sFALSE", BWHITE, feature_name, RED);
    }
}
