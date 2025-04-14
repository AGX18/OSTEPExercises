/**
 * @file ex4.c
 * @author your name (you@domain.com)
 * @brief 
 * execlp("ls", "ls", "-l", NULL);
 * 
 * @version 0.1
 * @date 2025-04-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>


int main() {
    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process: Executing 'ls -l'\n");
        execlp("ls", "ls", "-l", NULL); // Replace child process with 'ls -l'
        perror("execlp"); // If execlp fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process: Child has finished executing 'ls -l'\n");
    }

    return 0;
}