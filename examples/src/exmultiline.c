// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 4096 // Let's use the integrated buffer for our convenience.
#include "../../amp.h"


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 80, 3, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    amp_print_text(
        &amp, 0, amp_get_width(&amp)/2, 0, 0, AMP_ALIGN_CENTER,
        "In the beginning was the Word,\n"
        "and the Word was with God,\n"
        "and the Word was God."
    );

    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    return EXIT_SUCCESS;
}
