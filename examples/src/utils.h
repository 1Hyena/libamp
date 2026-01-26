// SPDX-License-Identifier: MIT
#ifndef UTILS_H_26_01_2026
#define UTILS_H_26_01_2026


static inline struct {
    char *data;
    size_t size;
} load_file(const char *fname) {
    static constexpr size_t INITIAL_BUFFER_CAPACITY = 512;
    size_t data_size = 0, data_capacity = INITIAL_BUFFER_CAPACITY;
    char *data = nullptr;
    typeof(load_file(nullptr)) blob = {};
    FILE *fp = fopen(fname, "r");

    if (fp == nullptr) {
        const char *error_message = "fopen: error opening file\n";
        write(2, error_message, strlen(error_message));

        return blob;
    }

    for (;;) {
        size_t bytes_read, bytes_to_read;

        data = realloc(data, data_capacity);

        if (data == nullptr) {
            const char *error_message = "realloc: memory allocation failed\n";
            write(2, error_message, strlen(error_message));

            return blob;
        }

        bytes_to_read = data_capacity - data_size;
        bytes_read = fread(data + data_size, 1, bytes_to_read, fp);
        data_size += bytes_read;

        if (bytes_read != bytes_to_read) {
            break;
        }

        data_capacity *= 2;
    }

    fclose(fp);

    blob.data = data;
    blob.size = data_size;

    return blob;
}

#endif
