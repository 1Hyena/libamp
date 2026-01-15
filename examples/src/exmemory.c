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
    size_t ansmap_size = amp_calc_size(width, height);
    uint8_t *ansmap = malloc(ansmap_size);

    if (!ansmap) {
        static const char message[] = "malloc: allocation failed\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    struct amp_type amp;

    if (amp_init(&amp, width, height, ansmap, ansmap_size) > ansmap_size) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    for (unsigned y=0; y<height; ++y) {
        for (unsigned x=0; x<width; ++x) {
            char glyph[] = {
                // Let's draw a random character.
                (char) random_uint64() % CHAR_MAX, '\0'
            };

            amp_draw_text(
                &amp,
                random_uint64(), // Let's enable random styles.
                x, y, AMP_ALIGN_LEFT, glyph
            );
        }
    }

    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_write("\n", 1);

    free(ansmap);

    return EXIT_SUCCESS;
}
