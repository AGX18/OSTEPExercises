/*
Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) 
and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable 
when both the child and parent change the value of x?

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>


int main() {
    int x = 100; // Initialize x in the parent process
    printf("Before fork, x = %d\n", x);
    pid_t pid = fork(); // Create a new process

    if (pid == 0) {
        // Child process
        printf("Child process: Before changing x, x = %d\n", x);
        x = 200; // Change x in the child process
        printf("Child process: After changing x, x = %d\n", x);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process: After child process, x = %d\n", x);
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return 0;
}