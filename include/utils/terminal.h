#ifndef _TERMINAL_H
#define _TERMINAL_H     1

#include <utils/arguments.h>

#define CLEAR_SCREEN() printf("\033[2J\033[H")
#define COLOUR(c) (get_arguments().no_ansi ? "" : (c))

/*
    GCC Colour Escape Codes (More Portable)
*/
#if defined(__GNUC__) && !defined(__MINGW32__)
#define BLACK     COLOUR("\e[0;30m")
#define RED       COLOUR("\e[0;31m")
#define GREEN     COLOUR("\e[0;32m")
#define YELLOW    COLOUR("\e[0;33m")
#define BLUE      COLOUR("\e[0;34m")
#define MAGENTA   COLOUR("\e[0;35m")
#define CYAN      COLOUR("\e[0;36m")
#define WHITE     COLOUR("\e[0;37m")

#define BBLACK    COLOUR("\e[1;30m")
#define BRED      COLOUR("\e[1;31m")
#define BGREEN    COLOUR("\e[1;32m")
#define BYELLOW   COLOUR("\e[1;33m")
#define BBLUE     COLOUR("\e[1;34m")
#define BMAGENTA  COLOUR("\e[1;35m")
#define BCYAN     COLOUR("\e[1;36m")
#define BWHITE    COLOUR("\e[1;37m")
#define RESET     COLOUR("\e[0m")
#endif

/*
    MINGW Colour Escape codes (For Windows CMD)
*/
#if defined(__MINGW32__)
#define BLACK     COLOUR("\x1b[0;30m")
#define RED       COLOUR("\x1b[0;31m")
#define GREEN     COLOUR("\x1b[0;32m")
#define YELLOW    COLOUR("\x1b[0;33m")
#define BLUE      COLOUR("\x1b[0;34m")
#define MAGENTA   COLOUR("\x1b[0;35m")
#define CYAN      COLOUR("\x1b[0;36m")
#define WHITE     COLOUR("\x1b[0;37m")

#define BBLACK    COLOUR("\x1b[1;30m")
#define BRED      COLOUR("\x1b[1;31m")
#define BGREEN    COLOUR("\x1b[1;32m")
#define BYELLOW   COLOUR("\x1b[1;33m")
#define BBLUE     COLOUR("\x1b[1:34m")
#define BMAGENTA  COLOUR("\x1b[1;35m")
#define BCYAN     COLOUR("\x1b[1;36m")
#define BWHITE    COLOUR("\x1b[1;37m")
#define RESET     COLOUR("\x1b[0m")
#endif

#endif