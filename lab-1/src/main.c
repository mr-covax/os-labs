#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char filepath[100];
    scanf("%s", filepath);

    // Opening up the file with numbers
    int file = open(filepath, O_RDONLY);
    if (file == -1) {
        perror("open");
        return 1;
    }

    // Creating pipes for IPC
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(2);
    }

    // Creating a child process
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return 2;
    }
    else if (pid == 0) {
        if (dup2(file, 0) == -1) {
            perror("dup2 with stdin");
            return 2;
        }
        if (dup2(pipefd[1], 1) == -1) {
            perror("dup2 with stdout");
            return 2;
        }
        if (execv("./calc", NULL) == -1) {
            perror("execv");
            return 2;
        };
    }
    else {
        char buffer[100];
        read(pipefd[0], buffer, 100);

        // This use this because the unused buffer space contains garbage,
        // and we don't want to print garbage in addition to the answer.
        float answer;
        sscanf(buffer, "%f", &answer);
        printf("%f\n", answer);
    }

    return 0;
}
