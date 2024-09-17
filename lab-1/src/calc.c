#include <stdio.h>

int main(void) {
    float buf;
    float answer = 0;

    while (scanf("%f", &buf) == 1)
        answer += buf;

    printf("%f", answer);
    return 0;
}
