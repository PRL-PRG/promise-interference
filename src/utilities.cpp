#include "utilities.h"
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/* https://stackoverflow.com/questions/8206387/using-non-printable-characters-as-a-delimiter-in-php
 */
const char RECORD_SEPARATOR = 0x1e;
const char UNIT_SEPARATOR = 0x1f;

std::pair<void *, std::size_t> mmap_file(const std::string &filepath) {

    int descriptor = open(filepath.c_str(), O_RDONLY);

    if (descriptor == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    struct stat file_info = {0};

    if (fstat(descriptor, &file_info) == -1) {
        perror("Error getting the file size");
        exit(EXIT_FAILURE);
    }

    if (file_info.st_size == 0) {
        return {};
    }

    // std::cerr << "File size is : " << file_info.st_size;

    void *data = mmap(NULL, file_info.st_size, PROT_READ,
                      MAP_PRIVATE | MAP_POPULATE, descriptor, 0);

    if (data == MAP_FAILED) {
        close(descriptor);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    return {data, file_info.st_size};
}

void munmap_file(void *data, std::size_t size) {
    if (munmap(data, size)) {
        perror("Error munmapping the file");
        exit(EXIT_FAILURE);
    }
}
