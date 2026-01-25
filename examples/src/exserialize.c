// SPDX-License-Identifier: MIT
#define AMP_BUF_SIZE 2048 // Let's use the integrated buffer for convenience.
#include "../../amp.h"


int main(int, char **) {
    struct amp_type amp;

    if (amp_init(&amp, 78, 2, nullptr, 0) > sizeof(amp.buffer)) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    amp_print_rich_text(
        &amp, amp_get_width(&amp) / 2, 0, AMP_STYLE_NONE, 0, AMP_ALIGN_CENTER,
        "{Nnavy background{X, {rred foreground{x, {/italic{x, {/{?faint italic"
    );

    // Write to stdout.
    amp_to_ans(&amp, nullptr, 0);
    const char *comment = "\n\nConverted to a plaintext AMP container:\n";
    amp_stdout(comment, strlen(comment));

    amp_serialize(&amp, AMP_FLATTEN|AMP_DEFLATE, nullptr, 0);
    amp_stdout("\n", 1);

    return EXIT_SUCCESS;
}
