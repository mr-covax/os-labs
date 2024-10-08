#ifndef _EXPERIMENT_H_
#define _EXPERIMENT_H_

#include <stdbool.h>

typedef struct {
    int rounds;
    int currentRound;
    int p1Score;
    int p2Score;
    int testRuns;
    int threads;
} expConfig;

bool expPrepareEnv(expConfig configuration);
bool expRun();
double expPlayerOneProb();
double expPlayerTwoProb();
bool expFreeEnv();

#endif