#include <math.h>
#include <stdlib.h>

float SinIntegral(float A, float B, float e) {
    float result = 0.0f;
    for (float x = A; x < B; x += e) {
        result += sinf(x) * e;
    }
    return result;
}

char* translation(long x) {
    char* converted = malloc(65);
    converted[64] = '\0';

    int index = 63;
    while (x) {
        converted[index--] = (x % 2) ? '1' : '0';
        x /= 2;
    }
    return &converted[index + 1];
}
