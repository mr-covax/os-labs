#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdbool.h>
#include <pthread.h>

typedef struct {
    double input;
    double output;
    bool working;
    pthread_mutex_t readable;
    pthread_mutex_t writable;
} info_t;

#endif