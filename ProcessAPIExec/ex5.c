/**
 * @file ex5.c
 * @author nagx
 * @brief 
 * 
 * Now write a program that uses wait() to wait for the child process to finish in the parent. 
 * What does wait() return? What happens if you use wait() in the child?
 * 
 * @version 0.1
 * @date 2025-04-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/**
 * If you use wait() in the child process, it will not wait for the parent process to finish. 
 * Instead, it will attempt to wait for its own child processes (if any). 
 * Since a newly forked child typically has no children of its own, wait() in the child will fail immediately with -1 and 
 * set errno to ECHILD ("No child processes").
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>


int main() {
    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        // sleep(2); // Simulate some work in the child
        wait(NULL); 
        exit(42); // Exit with a status code
    } else {
        // Parent process
        // int status;
        // pid_t child_pid = wait(&status); // Wait for the child process to finish

        // if (child_pid == -1) {
        //     perror("wait");
        //     exit(EXIT_FAILURE);
        // }
        // // The WIFEXITED(status) macro is used in Unix/Linux systems to check if a child process terminated normally 
        // if (WIFEXITED(status)) {
        //     printf("Parent process: Child with PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        // } else {
        //     printf("Parent process: Child with PID %d did not terminate normally\n", child_pid);
        // }

        sleep(1); // Simulate some work in the parent
        printf("Parent process: PID = %d\n", getpid());
    }

    return 0;
}