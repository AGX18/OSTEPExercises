/**
 * @file ex3.c
 * @author nagx
 * @brief 
 * Write another program using fork(). 
 * The child process should print “hello”; the parent process should print “goodbye”. 
 * You should try to ensure that the child process always prints first; 
 * can you do this without calling wait() in the parent?
 * 
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
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>


 int main() {
        pid_t pid = fork(); // Create a new process
    
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("hello\n");
        } else {
            // Parent process   
            sleep(1); // Sleep for 1 second to ensure child prints first
            
            printf("goodbye\n");
        }

    return 0;
 }