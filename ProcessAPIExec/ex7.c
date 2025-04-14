/**
 * @file ex7.c
 * @author nagx
 * @brief 
 * Write a program that creates a child process, and then in the child closes standard output (STDOUT_FILENO). 
 * What happens if the child calls printf() to print some output after closing the descriptor?

 * @version 0.1
 * @date 2025-04-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/*
it will not print anything to the console, as the standard output has been closed.
The output will be lost, and the program will not produce any visible output on the terminal.
*/

int main() {
    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(STDOUT_FILENO); // Close standard output
        printf("This will not be printed to the console.\n"); // Attempt to print
        fflush(stdout); // Flush the output buffer
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Child process has finished.\n");
    }

    return 0;
}