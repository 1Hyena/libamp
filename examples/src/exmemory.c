// SPDX-License-Identifier: MIT
#include "../../amp.h"


static uint64_t random_uint64() {
    uint32_t parts[2] = { arc4random(), arc4random() };
    return *((uint64_t *) parts);
}

int main(int, char **) {
    // If the memory required by the ansmap data structure exceeds what is
    // feasible for stack-based allocation, we should allocate the necessary
    // buffer from the heap.

    constexpr size_t width = 80;
    constexpr size_t height = 24;
    size_t buffer_size = amp_calc_size(width, height);
    uint8_t *buffer = malloc(buffer_size);

    if (!buffer) {
        static const char message[] = "malloc: allocation failed\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    struct amp_type amp;

    if (amp_init(&amp, width, height, buffer, buffer_size) > buffer_size) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        free(buffer);
        return EXIT_FAILURE;
    }

    for (unsigned y=0; y<height; ++y) {
        for (unsigned x=0; x<width; ++x) {
            char glyph[] = {
                // Let's draw a random character.
                (char) random_uint64() % CHAR_MAX, '\0'
            };

            amp_print_glyph(
                &amp, x, y,
                random_uint64(), // Let's enable random styles.
                glyph
            );
        }
    }

    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    free(buffer);

    return EXIT_SUCCESS;
}
