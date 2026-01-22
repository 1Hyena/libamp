// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 512 // Let's use the integrated buffer for convenience.
#include "../../amp.h"
#include <stdio.h>


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 40, 1, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    constexpr size_t rows = (
        sizeof(amp_inline_style_table) / sizeof(amp_inline_style_table[0])
    );

    char buf[64];

    for (size_t i = 0, n = 0; i < rows; ++i) {
        auto const row = amp_inline_style_table[i];

        if (row.glyph[0] == '\0') {
            continue;
        }

        ssize_t written = amp_snprint_rich_textf(
            &amp, 0, 0, 0, 0, AMP_ALIGN_LEFT, buf, sizeof(buf),
            " {{%s → {%ssample{x (%s)", row.glyph, row.glyph, row.name
        );

        if (written < (ssize_t) sizeof(buf) && written >= 0) {
            amp_to_ans(&amp, nullptr, 0); // Write to stdout.
            amp_clear(&amp);

            if (n++ % 2) {
                amp_stdout("\n", 1);
            }
        }
    }

    amp_stdout("\n", 1);
    amp_print_rich_text(
        &amp, 0, 0, 0, 0, AMP_ALIGN_LEFT,
        "{RA{rN{GS{gI {Bc{bo{Cl{co{Mr{ms {Ya{yr{We {wf{Du{xn{*!"
    );
    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    return EXIT_SUCCESS;
}
