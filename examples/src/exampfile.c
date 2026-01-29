// SPDX-License-Identifier: MIT
#include "../../amp.h"
#include "utils.h"


int main(int argc, char **argv) {
    const char *error_message = nullptr;

    if (argc < 2) {
        error_message = "this program requires an AMP file argument\n";
        write(2, error_message, strlen(error_message));
        return EXIT_FAILURE;
    }

    auto input_file = load_file(argv[1]);
    char *input_data = input_file.data;
    size_t input_size = input_file.size;

    if (!input_data) {
        return EXIT_FAILURE;
    }

    uint32_t w, h;
    size_t canvas_size = amp_doc_parse_size(input_data, input_size, &w, &h);
    uint8_t *canvas_data = nullptr;

    if (canvas_size) {
        canvas_data = malloc(canvas_size);

        if (canvas_data) {
            struct amp_type amp;

            if (amp_init(&amp, w, h, canvas_data, canvas_size) <= canvas_size) {
                if (amp_decode(&amp, input_data, input_size)) {
                    amp_set_palette(&amp, AMP_PAL_24BIT);
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

    free(input_data);
    free(canvas_data);

    if (error_message) {
        write(2, error_message, strlen(error_message));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
