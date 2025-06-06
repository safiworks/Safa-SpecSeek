#include <stdlib.h>
#include <unistd.h>
#include <utils/arguments.h>
#include <stdio.h>

static args_t arguments;

/// @brief changes the argument struct and applies settings based on arguments here
/// @param argc argument count (from main)
/// @param argv argument vector (from main)
void construct_arguments(int argc, const char** argv){
    for (int i = 1; i < argc; ++i){
        const char* arg = argv[i];

        ARG_MATCH(_ARGUMENT_VERBOSE) {
            if (i + 1 < argc){
                arguments.verbose = atoi(argv[++i]);
            }else{
                arguments.verbose = 1;
            }
        }
        
        ARG_MATCH(_ARGUMENT_NO_ANSI) { arguments.no_ansi = 1; }

        ARG_MATCH(_ARGUMENT_PUT_FEATURES_ON_NEWLINE) { arguments.put_features_on_newline = 1; }
    }

    // TTY check for pipe output purity. we do not want ansi codes there
    if(!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)){
        arguments.no_ansi = 1;
    }
}

args_t get_arguments(void){
    return arguments;
}

