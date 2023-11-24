#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "include/commands.h"
#include "include/terminal.h"

int main(int argc, char *argv[])
{

    Args lin_args;

    //< set default values for lin's arguments
    lin_args.all = 0;
    lin_args.commands = 0;
    lin_args.output = 0;
    lin_args.filename = "";
    //>

    // Invalid Command
    if (argc != 3)
    {
        fprintf(stderr, "\033[34mlin\033[0m: \033[31merror\033[0m: need an action option and filename\n");
        help(argv[0]);
        exit(EXIT_FAILURE); /* Exit with failure */
    }

    // get filename
    lin_args.filename = argv[2];

    // get argument
    char *argument = argv[1];

    //< Set saving option
    if ((strcmp("--commands", argument) == 0) || (strcmp("-c", argument)) == 0)
    {
        lin_args.commands = 1; // set lin argument to commands
    }
    else if ((strcmp("--output", argument) == 0) || (strcmp("-o", argument)) == 0)
    {
        lin_args.output = 1; // set lin argument to output
    }
    else
    {
        lin_args.all = 1; // Default: set lin argument to all
    }
    //>

    // open lin's sub-terminal
    terminal(lin_args);

    return 0;
}