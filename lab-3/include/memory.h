#ifndef _SHARED_H
#define _SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

void* create_shm(const char* shm_name, size_t shm_size) {
    if (shm_name == NULL || shm_size == 0) {
        return NULL;
    }

    // Create or open the shared memory object
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Resize the shared memory object to the specified size
    if (ftruncate(shm_fd, shm_size) == -1) {
        perror("ftruncate");
        close(shm_fd);
        shm_unlink(shm_name);
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the process's address space
    void* mapped_region = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (mapped_region == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        shm_unlink(shm_name);
        return NULL;
    }

    // Close the file descriptor as it's no longer needed after mmap
    close(shm_fd);

    return mapped_region;
}

void remove_shm(const char* shm_name, void* ptr, size_t size) {
    if (ptr == NULL || size == 0)
        return;

    if (munmap(ptr, size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink(shm_name) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }
}

#endif