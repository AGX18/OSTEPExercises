/**
 * @file ex2.c
 * @author nagx
 * @brief 
 * @version 0.1
 * @date 2025-04-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 /**
  * @brief 
  * Write a program that opens a file (with the open() system call) and 
  * then calls fork() to create a new process. Can both the child and parent access the file descriptor 
  * returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?
  * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Open a file for writing
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        const char *child_msg = "Hello from child process!\n";
        write(fd, child_msg, strlen(child_msg));
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        const char *parent_msg = "Hello from parent process!\n";
        write(fd, parent_msg, strlen(parent_msg));
        close(fd);
        wait(NULL); // Wait for the child process to finish
    }
    return 0;
}