#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
    char new_output_file[MAX_INPUT_SIZE];
    char* target_name = strrchr(executable_path, '/');

    if(target_name != NULL) target_name++; // if executable_path includes "/", get the substring after the last "/"
    else target_name = executable_path;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        generate_input(input);

        snprintf(output_file, sizeof(output_file), "%s%s_output_%d.txt", OUT_FILE_PATH, target_name, i);

        int pid = fork();

        if (pid == 0) { // child process
            freopen(output_file, "w", stdout); // redirect stdout to output_file
            freopen(output_file, "a", stderr); // redirect stderr to output_file, appending
            execl(executable_path, executable_path, input, NULL);
            perror("execl");
            return 1;
        } else if (pid > 0) { // parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFSIGNALED(status)) {
                printf("The program crashed on iteration %d with input: %s, signal: %d\n", i, input, WTERMSIG(status));
                snprintf(new_output_file, sizeof(new_output_file), "%s%s_output_%d_%d.txt", OUT_FILE_PATH, target_name, WTERMSIG(status), i);
                rename(output_file, new_output_file); // rename the file with signal number
                return 1;
            }
        } else { // fork failed
            perror("fork");
            return 1;
        }
    }
    return 0;
}
