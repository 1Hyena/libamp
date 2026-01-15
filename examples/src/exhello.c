// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 256 // Let's use the integrated buffer for our convenience.
#include "../../amp.h"


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 16, 1, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, sizeof(message));
        return EXIT_FAILURE;
    }

    amp_draw_text(&amp, AMP_BLINKING, 0, 0, AMP_ALIGN_LEFT, "Hello, world!");
    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_write("\n", 1);

    return EXIT_SUCCESS;
}
