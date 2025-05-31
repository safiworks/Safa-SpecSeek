#ifndef _TERMINAL_H
#define _TERMINAL_H     1

#define CLEAR_SCREEN() printf("\033[2J\033[H")

/*
    GCC Colour Escape Codes (More Portable)
*/
#if defined(__GNUC__) && !defined(__MINGW32__)
#define BLACK   "\e[0;30m"
#define RED     "\e[0;31m"
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define BLUE    "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN    "\e[0;36m"
#define WHITE   "\e[0;37m"

#define BBLACK   "\e[1;30m"
#define BRED     "\e[1;31m"
#define BGREEN   "\e[1;32m"
#define BYELLOW  "\e[1;33m"
#define BBLUE    "\e[1;34m"
#define BMAGENTA "\e[1;35m"
#define BCYAN    "\e[1;36m"
#define BWHITE   "\e[1;37m"
#define RESET    "\e[0m"
#endif

/*
    MINGW Colour Escape codes (For Windows)
    these are more strict, using the GNUC based escape
    codes works, however it leaves residual characters because
    ofc it does.
*/
#if defined(__MINGW32__)
#define BLACK   "\x1b[0;30m"
#define RED     "\x1b[0;31m"
#define GREEN   "\x1b[0;32m"
#define YELLOW  "\x1b[0;33m"
#define BLUE    "\x1b[0;34m"
#define MAGENTA "\x1b[0;35m"
#define CYAN    "\x1b[0;36m"
#define WHITE   "\x1b[0;37m"

#define BBLACK   "\x1b[1;30m"
#define BRED     "\x1b[1;31m"
#define BGREEN   "\x1b[1;32m"
#define BYELLOW  "\x1b[1;33m"
#define BBLUE    "\x1b[1;34m"
#define BMAGENTA "\x1b[1;35m"
#define BCYAN    "\x1b[1;36m"
#define BWHITE   "\x1b[1;37m"

#define RESET    "\x1b[0m"
#endif

#endif