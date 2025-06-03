#ifndef _TERMINAL_H
#define _TERMINAL_H     1

#define CLEAR_SCREEN() printf("\033[2J\033[H")

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[94m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define BBLACK   "\033[30m"
#define BRED     "\033[31m"
#define BGREEN   "\033[32m"
#define BYELLOW  "\033[33m"
#define BBLUE    "\033[34m"
#define BMAGENTA "\033[35m"
#define BCYAN    "\033[36m"
#define BWHITE   "\033[37m"
#define RESET    "\033[0m"

#endif