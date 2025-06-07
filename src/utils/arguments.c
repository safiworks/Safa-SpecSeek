#include <stdlib.h>
#include <unistd.h>
#include <utils/arguments.h>
#include <utils/terminal.h>
#include <stdio.h>

static args_t arguments;

/// @brief changes the argument struct and applies settings based on arguments here
/// @param argc argument count (from main)
/// @param argv argument vector (from main)
/// @return Success?
int construct_arguments(int argc, const char** argv){
    for (int i = 1; i < argc; ++i){
        const char* arg = argv[i];

        ARG_MATCH(_ARGUMENT_VERBOSE) { arguments.verbose = (i + 1 < argc && argv[i + 1][0] != '-') ? atoi(argv[++i]) : 1; return 0;}
        ARG_MATCH(_ARGUMENT_NO_ANSI) { arguments.no_ansi = 1; return 0; }
        ARG_MATCH(_ARGUMENT_PUT_FEATURES_ON_NEWLINE) { arguments.put_features_on_newline = 1; return 0;}

        printf("%s%s%s is not a valid argument, use --help to see a list of commands, aborting%s\n", BRED, argv[i], RED, RESET);
        fflush(stdout);
        return 1;
    }

    // TTY check for pipe output purity. we do not want ansi codes there
    if(!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)){
        arguments.no_ansi = 1;
    }

    return 0;
}

args_t get_arguments(void){
    return arguments;
}

