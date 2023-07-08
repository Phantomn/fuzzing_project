#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 256
#define NUM_ITERATIONS 10
#define OUT_FILE_PATH "out/"

void generate_input(char* buffer) {
    for (int i = 0; i < MAX_INPUT_SIZE - 1; i++) {
        buffer[i] = 'A' + (rand() % 26);  // Generate a random uppercase letter
    }
    buffer[MAX_INPUT_SIZE - 1] = '\0';  // Null terminate the string
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [path_to_executable]\n", argv[0]);
        return 1;
    }

    char* executable_path = argv[1];
    char input[MAX_INPUT_SIZE];
    char output_file[MAX_INPUT_SIZE];
    int pipefd[2];

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        generate_input(input);

        snprintf(output_file, sizeof(output_file), "%soutput_%d.txt", OUT_FILE_PATH, i);

        if (pipe(pipefd) == -1) {
            perror("pipe failed");
            return 1;
        }

        int pid = fork();
        if (pid == 0) { // child process
            close(pipefd[1]);  // Close unused write end

            if (dup2(pipefd[0], STDIN_FILENO) == -1) {
                perror("dup2 failed");
                exit(1);
            }

            freopen(output_file, "w", stdout); // redirect stdout to output_file
            freopen(output_file, "a", stderr); // redirect stderr to output_file, appending
            execl(executable_path, executable_path, NULL);
            perror("execl failed");
            exit(1);
        } else if (pid > 0) { // parent process
            close(pipefd[0]);  // Close unused read end

            write(pipefd[1], input, strlen(input));
            close(pipefd[1]);  // Close write end of the pipe

            int status;
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status)) {
                printf("The program crashed on iteration %d with input: %s, signal: %d\n", i, input, WTERMSIG(status));
                return 1;
            }
        } else { // fork failed
            perror("fork failed");
            return 1;
        }
    }

    return 0;
}
