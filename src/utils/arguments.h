#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H 1
#include <string.h>

#define _ARGUMENT_VERBOSE "--verbose"
#define _ARGUMENT_PUT_FEATURES_ON_NEWLINE "--features-on-newline"


#define IF_VERBOSE(level, args) if ((args).verbose >= (level))
#define ARG_MATCH(x) if (strcmp(arg, x) == 0)

typedef struct args{
    int verbose;
    int put_features_on_newline;
}args_t;


extern args_t arguments;

/// @brief changes the argument struct and applies settings based on arguments here
/// @param argc argument count (from main)
/// @param argv argument vector (from main)
/// @param args argument structure reference
void construct_arguments(int argc, const char** argv);

#endif