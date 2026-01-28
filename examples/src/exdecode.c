// SPDX-License-Identifier: MIT
#include "../../amp.h"


int main(int, char **) {
    const char *error_message = nullptr;
    static const char doc[] =
        "╔════════════════╗\n"
        "╠════════════════╣\n"
        "║    WS    SW  AA║\n"
        "║    OOOOOOOO  AA║\n"
        "║    OOMRLLMR  OO║\n"
        "║    CCLLLLLL  OO║\n"
        "║OOCCOOCCOOCCOOLL║\n"
        "║LLLLCCOOCCOO  OO║\n"
        "║  MMMMMMMMMM  OO║\n"
        "║  CC      CC  OO║\n"
        "╚════════════════╝";
    uint32_t w, h;
    size_t data_size = amp_doc_parse_size(doc, sizeof(doc), &w, &h);
    uint8_t *data = nullptr;

    if (data_size) {
        data = malloc(data_size);

        if (data) {
            struct amp_type amp;

            if (amp_init(&amp, w, h, data, data_size) <= data_size) {
                if (amp_decode(&amp, doc, sizeof(doc))) {
                    amp_to_ans(&amp, nullptr, 0);
                    amp_stdout("\n", 1);
                }
                else error_message = "amp_decode: parse error\n";
            }
            else error_message = "amp_init: not enough memory provided\n";
        }
        else error_message = "malloc: allocation failed\n";
    }
    else error_message = "amp_parse_size: parse error\n";

    free(data);

    if (error_message) {
        write(2, error_message, strlen(error_message));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
