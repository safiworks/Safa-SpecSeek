#ifndef _ASCIIART_H
#define _ASCIIART_H  1

#include <stdio.h>

// A Macro that prints a small banner with colour customisation
// and a title argument so I can reuse it.
#define ASCII_BANNER(title, colour) \
    printf(colour "===========================\n" \
                  "   %s                        \n" \
                  "===========================\n" RESET, title)


#define ASCII_DIVIDER(title, colour) \
    printf(colour "\n=============== %s ==============\n" RESET, title)
#define ASCII_DIVIDER_NOTEXT(colour) \
    printf(colour "\n=================================\n" RESET)

#define ASCII_DIVIDER_SMALL(title, colour) \
    printf(colour "\n~~~~~~~~~~ %s ~~~~~~~~~~\n" RESET, title)

#define ASCII_DIVIDER_SMALL_NOTEXT(colour) \
    printf(colour "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" RESET)

#endif