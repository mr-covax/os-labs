#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/random.h>

#include "experiment.h"

typedef struct {
    int occupied;
    int *results;
    pthread_mutex_t mtx;
} expRuntime;

expConfig cfg;
expRuntime vars = {0, NULL, 0};

int throw_dice() {
    int output[2];
    getrandom(output, sizeof(output), 0);
    return (output[0] % 6) + (output[1] % 6) + 2;
}

void* workerCode(void *args) {
    int turns = cfg.rounds - cfg.currentRound;

    while (true) {
        pthread_mutex_lock(&vars.mtx);
        int cell = vars.occupied++;
        pthread_mutex_unlock(&vars.mtx);

        if (cell >= cfg.testRuns)
            pthread_exit(0);

        int score_1 = cfg.p1Score;
        int score_2 = cfg.p2Score;
        for (int i = 0; i < turns; ++i) {
            score_1 += throw_dice();
            score_2 += throw_dice();
        }

        if (score_1 > score_2) {
            vars.results[cell] = 1;
        } else if (score_1 < score_2) {
            vars.results[cell] = 2;
        } else {
            vars.results[cell] = 0;
        }
    }
}

bool expFreeEnv() {
    pthread_mutex_destroy(&vars.mtx);
    if (vars.results != NULL) {
        free(vars.results);
    }
    vars.results = NULL;
    vars.occupied = 0;
}

bool expPrepareEnv(expConfig configuration) {
    cfg = configuration;
    expFreeEnv();
    vars.occupied = 0;
    vars.results = malloc(sizeof(int) * cfg.testRuns);
    pthread_mutex_init(&vars.mtx, NULL);
}

bool expRun() {
    pthread_t threads[cfg.threads];
    for (int i = 0; i < cfg.threads; ++i) {
        pthread_create(&threads[i], NULL, workerCode, NULL);
    }
    for (int i = 0; i < cfg.threads; ++i) {
        pthread_join(threads[i], NULL);
    }
}

double getPlayerProbability(int playerNum) {
    int wins = 0;
    for (int i = 0; i < cfg.testRuns; ++i) {
        wins += (vars.results[i] == playerNum);
    }
    return (double)wins / cfg.testRuns;
}

double expPlayerOneProb() {
    return getPlayerProbability(1);
}

double expPlayerTwoProb() {
    return getPlayerProbability(2);
}