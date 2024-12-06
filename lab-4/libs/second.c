#include <math.h>
#include <stdlib.h>

float SinIntegral(float A, float B, float e) {
    float result = 0.0f;
    for (float x = A; x < B; x += e) {
        result += (sinf(x) + sinf(x + e)) / 2 * e;
    }
    return result;
}

char* translation(long x) {
    char* converted = (char*)malloc(65);
    converted[64] = '\0';
    int index = 63;

    while (x) {
        converted[index--] = (x % 3) + '0';
        x /= 3;
    }
    return &converted[index + 1];
}
