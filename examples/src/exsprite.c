// SPDX-License-Identifier: MIT
#include "../../amp.h"


const unsigned char spr_file[] = {
    #embed "../tiles.amp" if_empty('M', 'i', 's', 's', 'i', 'n', 'g', '\n')
    , '\0'
};


int main(int, char **) {
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
        spr_file, sizeof(spr_file), &spr_w, &spr_h
    );

    uint8_t *spr_data = nullptr;

    if (spr_size) {
        spr_data = malloc(spr_size);

        if (spr_data) {
            struct amp_type spr;

            if (amp_init(&spr, spr_w, spr_h, spr_data, spr_size) <= spr_size) {
                if (amp_deserialize(&spr, spr_file, sizeof(spr_file))) {
                    amp_draw_sprite(&canvas, 0, 0, &spr);
                }
                else error_message = "amp_deserialize: parse error\n";
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

    if (error_message) {
        write(2, error_message, strlen(error_message));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
