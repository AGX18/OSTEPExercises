/**
 * @file ex6.c
 * @author your name (you@domain.com)
 * @brief 
 * 
 * Write a slight modification of the previous program, this time using waitpid() instead of wait(). 
 * When would waitpid() be useful?


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
        int status;
        // the waitpid() function is used to wait for a specific child process to finish
        /**
         * @brief 
         * 0 → Blocks until child exits (default).
         * • WNOHANG → Returns immediately if no child has exited.
         * • WUNTRACED → Also returns if child is stopped (not terminated).
         * • WCONTINUED → Also returns if a stopped child resumes.
         * 
         */
        pid_t child_pid = waitpid(pid, &status, 0); // Wait for the specific child process to finish

        /**
         * @brief return value of waitpid()
         * > 0 → PID of the child that changed state.
         * -1 → Error (e.g., no children, ECHILD).
         * 0 → (Only if WNOHANG is used) No child exited yet.
         * 
         */

        if (child_pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Parent process: Child with PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        } else {
            printf("Parent process: Child with PID %d did not terminate normally\n", child_pid);
        }
    }

    return 0;
}