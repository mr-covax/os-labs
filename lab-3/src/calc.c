#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>

#include "memory.h"
#include "structs.h"

int main(void) {
    const char* shm_name = "Calc Shared";
    info_t* data = create_shm(shm_name, sizeof(info_t));

    while (true) {
        pthread_mutex_lock(&data->readable);
        if (!data->working)
            break;
        data->output += data->input;
        pthread_mutex_unlock(&data->writable);
    }

    remove_shm(shm_name, data, sizeof(info_t));
    return 0;
}
