#ifndef LIN_TERMINAL
#define LIN_TERMINAL

#include "commands.h"

/* lin terminal */
extern void terminal(Args lin_args);
extern char *get_terminal_prefix(const char *cwd);

#endif // LIN_TERMINAL
