// SPDX-License-Identifier: MIT
#include "../../amp.h"
#include "utils.h"


int main(int argc, char **argv) {
    auto spr_blob = load_file("../tiles.amp");

    if (!spr_blob.data) {
        return EXIT_FAILURE;
    }

    constexpr size_t width = 80;
    constexpr size_t height = 24;

    size_t canvas_size = amp_calc_size(width, height);
    uint8_t *canvas_data = malloc(canvas_size);

    if (!canvas_data) {
        static const char message[] = "malloc: allocation failed\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    struct amp_type canvas;
    amp_init(&canvas, width, height, canvas_data, canvas_size);

    const char *error_message = nullptr;
    uint32_t spr_w, spr_h;
    size_t spr_size = amp_parse_size(
        spr_blob.data, spr_blob.size, &spr_w, &spr_h
    );

    uint8_t *spr_data = nullptr;

    if (spr_size) {
        spr_data = malloc(spr_size);

        if (spr_data) {
            struct amp_type spr;

            if (amp_init(&spr, spr_w, spr_h, spr_data, spr_size) <= spr_size) {
                if (amp_decode(&spr, spr_blob.data, spr_blob.size)) {
                    amp_draw_sprite(&canvas, 0, 0, &spr);
                }
                else error_message = "amp_decode: parse error\n";
            }
            else error_message = "amp_init: not enough memory provided\n";
        }
        else error_message = "malloc: allocation failed\n";
    }
    else error_message = "amp_parse_size: parse error\n";

    if (!error_message) {
        amp_set_palette(&canvas, AMP_PAL_24BIT);
        amp_to_ans(&canvas, nullptr, 0); // Write to stdout.
        amp_stdout("\n", 1);
    }

    free(spr_data);
    free(canvas_data);
    free(spr_blob.data);

    if (error_message) {
        write(2, error_message, strlen(error_message));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
