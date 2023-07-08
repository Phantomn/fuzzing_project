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

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        generate_input(input);

        snprintf(output_file, sizeof(output_file), "%soutput_%d.txt", OUT_FILE_PATH, i);

        int pid = fork();

        if (pid == 0) { // child process
            freopen(output_file, "w", stdout); // redirect stdout to output_file
            freopen(output_file, "a", stderr); // redirect stderr to output_file, appending
            execl(executable_path, executable_path, input, NULL);
            perror("execl failed");
            exit(1);
        } else if (pid > 0) { // parent process
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
