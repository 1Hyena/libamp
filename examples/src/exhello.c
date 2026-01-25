// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 256 // Let's use the integrated buffer for our convenience.
#include "../../amp.h"


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 16, 1, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    amp_print_line(&amp, 0, 0, AMP_BLINKING, AMP_ALIGN_LEFT, "Hello, world!");
    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    return EXIT_SUCCESS;
}
