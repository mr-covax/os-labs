#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>

typedef float (*SinIntegralFunc)(float, float, float);
typedef char* (*TranslationFunc)(long);

struct Impl {
    void* library;
    SinIntegralFunc sinIntegral;
    TranslationFunc translation;
};

struct Impl loadImpl(const char* library) {
    void* dyn_lib = dlopen(library, RTLD_LAZY);
    if (!dyn_lib) {
        perror("dlopen");
        exit(EXIT_FAILURE);
    }

    struct Impl functions;
    functions.library = dyn_lib;
    functions.sinIntegral = (SinIntegralFunc)dlsym(dyn_lib, "SinIntegral");
    functions.translation = (TranslationFunc)dlsym(dyn_lib, "translation");

    if (!functions.sinIntegral || !functions.translation) {
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    return functions;
}

void closeImpl(struct Impl impl) {
    dlclose(impl.library);
}

int main() {
    int i = 0;
    struct Impl implementations[2] = {
        loadImpl("./libfirst.so"), 
        loadImpl("./libsecond.so")
    };

    printf("Libraries loaded! Listening for your commands...\n");

    int command;
    while (scanf("%d", &command) == 1) {
        if (command == 1) {
            float a, b, c;
            scanf("%f %f %f", &a, &b, &c);
            float answer = implementations[i].sinIntegral(a, b, c);
            printf("%f\n", answer);
        }
        else if (command == 2) {
            long a;
            scanf("%ld", &a);
            char* answer = implementations[i].translation(a);
            printf("%s\n", answer);
        }
        else if (command == 0) {
            i = (i + 1) % 2;
            printf("Switched the library.\n");
        }
        else {
            break;
        }
    }

    return 0;
}
