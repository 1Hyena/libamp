// SPDX-License-Identifier: MIT
#include "../../amp.h"
#include "utils.h"


static void draw_dungeon(struct amp_type *canvas, const struct amp_type *tiles);


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
    uint8_t *spr_data = nullptr;

    do {
        uint32_t spr_w, spr_h;
        size_t spr_size = amp_doc_parse_size(
            spr_blob.data, spr_blob.size, &spr_w, &spr_h
        );

        if (!spr_size) {
            error_message = "amp_parse_size: parse error\n";
            break;
        }

        if ((spr_data = malloc(spr_size)) == nullptr) {
            error_message = "malloc: allocation failed\n";
            break;
        }

        struct amp_type spr;

        if (amp_init(&spr, spr_w, spr_h, spr_data, spr_size) > spr_size) {
            error_message = "amp_init: not enough memory provided\n";
            break;
        }

        if (!amp_decode(&spr, spr_blob.data, spr_blob.size)) {
            error_message = "amp_decode: parse error\n";
            break;
        }

        draw_dungeon(&canvas, &spr);
    } while (false);

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

static void draw_dungeon(
    struct amp_type *canvas, const struct amp_type *tiles
) {
    constexpr uint8_t dungeon_w = 10;
    constexpr uint8_t dungeon_h = 6;
    constexpr uint8_t dungeon_d = 2;

    static const uint8_t dungeon[dungeon_d][dungeon_h][dungeon_w] = {
        {
            { 4, 4, 4, 4, 5, 5, 4, 4, 4, 4 },
            { 4, 4, 5, 5, 5, 5, 5, 4, 4, 4 },
            { 5, 5, 5, 5, 5, 4, 5, 5, 5, 4 },
            { 4, 4, 5, 5, 5, 4, 5, 5, 4, 4 },
            { 4, 4, 4, 4, 5, 5, 5, 4, 4, 4 },
            { 4, 4, 4, 4, 4, 5, 5, 4, 4, 4 }
        },
        {
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 1, 0, 3, 0 },
            { 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        }
    };

    for (long d=0; d<dungeon_d; ++d) {
        for (long y=0; y<dungeon_h; ++y) {
            for (long x=0; x<dungeon_w; ++x) {
                uint8_t tile_index = dungeon[d][y][x];

                if (!tile_index) {
                    continue;
                }

                tile_index--;

                uint8_t tile_w = 8;
                uint8_t tile_h = 4;
                long tile_from_x = tile_w * tile_index + tile_index;
                long tile_from_y = 0;
                long tile_to_x = tile_w * x;
                long tile_to_y = tile_h * y;

                amp_draw_ansmap_region(
                    canvas, tile_to_x, tile_to_y,
                    tiles, tile_from_x, tile_from_y, tile_w, tile_h
                );
            }
        }
    }
}
