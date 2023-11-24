#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "include/terminal.h"
#include "include/commands.h"

void terminal(Args lin_args)
{
    char *user_input;
    char *cwd = (char *)malloc(sizeof(char) * 1024);

    // Readline setup
    using_history(); // Enable history

    for (;;)
    {
        // Get current working directory
        if (cwd != NULL)
        {
            getcwd(cwd, 1024);
        }
        else
        {
            perror("getcwd");
        }

        char *terminal_prefix = get_terminal_prefix(cwd);

        // Read input with history support
        user_input = readline(terminal_prefix);

        // Check for exit condition
        if (user_input == NULL || strcmp(user_input, "lin exit") == 0)
        {
            free(user_input);
            break;
        }

        // Add the command to history
        add_history(user_input);

        // Execute the command and display the output
        execute_command(user_input, lin_args);

        // Free the memory allocated by readline
        free(user_input);

        // Free the memory allocated by get_terminal_prefix
        free(terminal_prefix);
    }

    // Free cwd
    free(cwd);

    // Clean up Readline
    clear_history();
}

char *get_terminal_prefix(const char *cwd)
{
    // Calculate the length needed for the final string
    size_t len = strlen(cwd) + 50; // 50 for the color codes and "(lin) " + "$ "

    // Allocate memory for the final string
    char *terminal_prefix = (char *)malloc(len + 1); // +1 for the null terminator

    if (terminal_prefix == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Construct the final string
    snprintf(terminal_prefix, len + 1, "\033[34m(lin)\033[0m\033[35m%s\033[0m$ ", cwd); // Blue color for "(lin)", Magenta color for text, and Reset color before "$ "

    return terminal_prefix;
}