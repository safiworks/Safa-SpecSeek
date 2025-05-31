#ifndef _ASCIIART_H
#define _ASCIIART_H  1

#include <stdio.h>

// A Macro that prints a small banner with colour customisation
// and a title argument so I can reuse it.
#define ASCII_BANNER(colour, title) \
    printf(colour "===========================\n" \
                  "   %s                        \n" \
                  "===========================\n" RESET, title)

#endif