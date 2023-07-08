#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    unsigned int length;
    char* data;

    printf("Enter the length of the data: ");
    length = atoi(argv[1]);

    // Integer overflow vulnerability if length + 1 overflows
    data = malloc((length + 1) * sizeof(char));
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    // Initialize the data
    for (unsigned int i = 0; i < length; i++) {
        data[i] = 'A';
    }
    data[length] = '\0';

    printf("Data: %s\n", data);

    // Free the memory
    free(data);

    return 0;
}
