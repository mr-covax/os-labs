#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "memory.h"
#include "structs.h"

int main(void) {
    char filepath[100];
    scanf("%s", filepath);

    // Opening up the file with numbers
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Creating the shared memory channel
    const char* shm_name = "Calc Shared";
    info_t* data = create_shm(shm_name, sizeof(info_t));

    // Configure the initial state of the shared structure
    data->working = 1;
    data->input = data->output = 0;

    // Set up mutexes
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&data->readable, &attr);
    pthread_mutex_init(&data->writable, &attr);
    pthread_mutex_lock(&data->readable);

    // Creating a child process
    int pid = fork();
    if (pid == -1) {
        perror("fork");
        return 2;
    }
    else if (pid == 0) {
        if (execv("./Calc", NULL) == -1) {
            perror("execv");
            exit(2);
        };
    }
    else {
        double buffer;
        while (fscanf(file, "%lf", &buffer) == 1) {
            pthread_mutex_lock(&data->writable);
            data->input = buffer;
            pthread_mutex_unlock(&data->readable);
        }

        pthread_mutex_lock(&data->writable);
        printf("%lf\n", data->output);
        
        data->working = 0;
        remove_shm(shm_name, data, sizeof(info_t));
    }

    return 0;
}
