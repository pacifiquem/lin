#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "include/commands.h"
#define MAX_OUTPUT_SIZE 500

void save_commands_and_output(const char *output, const char *command, const Args lin_args)
{
    // Open file to save command and its output
    FILE *file = fopen(lin_args.filename, "a");

    // Check if the file was opened successfully
    if (file == NULL)
    {
        fprintf(stderr, "Lin: Error: Failed to open file: %s", lin_args.filename);
        exit(EXIT_FAILURE);
    }

    if (lin_args.commands)
    {
        fprintf(file, "%s\n", command); // Save commands only with newline
    }
    else if (lin_args.output)
    {
        fprintf(file, "%s\n", output); // Save output only with newline
    }
    else
    {
        fprintf(file, "Command:\n\t%s\nOutput:\n\t%s", command, output); // Save both command and output with newline
    }
    fprintf(file, "%s\n", "------------------");

    fclose(file);

    printf("%s\n", output);
}

int execute_command(const char *command, Args lin_args)
{
    FILE *fp;
    char output[MAX_OUTPUT_SIZE];
    char aggregated_output[MAX_OUTPUT_SIZE * 24]; // maximum aggregated output we can store

    /* Handle cd command. */
    char *p = strstr(command, "cd "); // check if the command is *cd*
    if (p != NULL && (p == command))
    {
        // Extract the directory path after "cd "
        const char *dir_path = p + strlen("cd ");

        // Trim leading and trailing whitespaces
        while (*dir_path == ' ' || *dir_path == '\t')
        {
            ++dir_path;
        }

        size_t len = strlen(dir_path);
        while (len > 0 && (dir_path[len - 1] == ' ' || dir_path[len - 1] == '\t'))
        {
            --len;
        }

        // Create a null-terminated string with the directory path
        char dir[len + 1];
        strncpy(dir, dir_path, len);
        dir[len] = '\0';

        // Use chdir with the extracted directory path
        if (chdir(dir) != 0)
        {
            perror("chdir");
            return -1;
        }
        
        /*
            No need to proceed further if it's a cd command
            We won't save any info for cd commands
        */
        return 0;
    }
    else
    {

        // For other commands
        if ((strcmp(command, "exit") == 0) || (strcmp(command, "quit") == 0))
            exit(0);

        // Open a pipe to the command
        fp = popen(command, "r");
        if (fp == NULL)
        {
            perror("Error opening pipe");
            return -1;
        }
    }

    // Read the command output
    aggregated_output[0] = '\0'; // Initialize aggregated_output as an empty string
    while (fgets(output, sizeof(output), fp) != NULL)
    {
        // Append the current output to aggregated_output
        strncat(aggregated_output, output, sizeof(aggregated_output) - strlen(aggregated_output) - 1);
    }

    if (strlen(aggregated_output) == 0)
    {
        strcpy(aggregated_output, "No output!\n"); // New line for commands that return no output
    }

    // Save info.
    save_commands_and_output(aggregated_output, command, lin_args);

    // Close the pipe
    pclose(fp);

    return 0;
}

void help(const char *command)
{
    printf(
        "\nSave your terminal session's commands and output into a file with an ease. \n \n"
        "Usage: \033[36mlin --option filename\033[0m \n \n"
        "Arguments: \n"
        "\t \033[34m--all, -a\033[0m     :   save both commands and their output.\n"
        "\t \033[34m--output, -o\033[0m  :   save only output of commands.\n"
        "\t \033[34m--commands, -c\033[0m :   save only commands.\n\n"
        "Default option is \033[34m--all\033[0m\n\n");
}
