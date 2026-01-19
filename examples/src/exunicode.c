// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 2048 // Let's use the integrated buffer for convenience.
#include "../../amp.h"


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 16, 8, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    for (long y = 1; y < amp.height; ++y) {
        for (long x = 1; x < amp.width; ++x) {
            amp_draw_glyph(&amp, AMP_BG_GRAY, x, y, "▒");
        }
    }

    amp_draw_multiline_text(
        &amp, AMP_BG_BLUE|AMP_FG_WHITE, 0, 0, 0, AMP_ALIGN_LEFT,
        "╔═════════════╗\n"
        "║             ║\n"
        "║             ║\n"
        "║             ║\n"
        "║             ║\n"
        "║             ║\n"
        "╚═════════════╝\n"
        ""
    );

    amp_draw_multiline_text(
        &amp, AMP_FG_RED|AMP_BG_NAVY, 1, 1, amp.width - 3, AMP_ALIGN_LEFT,
        "In this example, we also see text wrapping in action."
    );

    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    return EXIT_SUCCESS;
}
