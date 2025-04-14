/**
 * @file ex8.c
 * @author nagx
 * @brief 
 * Write a program that creates two children, and connects the standard output of one to the standard input of the other, 
 * using the pipe() system call.
 * 
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

int main() {
    int pipefd[2]; // Array to hold the file descriptors for the pipe
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child 1: Close the read end of the pipe and write to the pipe
        close(pipefd[0]); // Close unused read end
        const char *message = "Hello from Child 1\n";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]); // Close write end after writing
        exit(0);
    }

    // Create the second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child 2: Close the write end of the pipe and read from the pipe
        close(pipefd[1]); // Close unused write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child 2 received: %s", buffer);
        close(pipefd[0]); // Close read end after reading
        exit(0);
    }

    // Parent process: Close both ends of the pipe and wait for children to finish
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL); // Wait for Child 1
    wait(NULL); // Wait for Child 2

    return 0;
}