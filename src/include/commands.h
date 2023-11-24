#ifndef LIN_COMMANDS
#define LIN_COMMANDS

#include <stdbool.h>

/* Lin arguments */
typedef struct
{
    bool all;
    bool output;
    bool commands;
    const char *filename;
} Args;

/* Save commands and their output to a given file.*/
extern void save_commands_and_output(const char* output, const char* command, const Args* lin_args);

/* Execute user's commands */
extern int execute_command(const char *command, Args lin_args);

/* Print help */
extern void help(const char *command);

#endif //LIN_COMMANDS
