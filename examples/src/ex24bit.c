// SPDX-License-Identifier: MIT
#include "../../amp.h"
#include <math.h>


static void draw_palette(struct amp_type *amp);

int main(int, char **) {
    constexpr size_t width = 80;
    constexpr size_t height = 24;
    size_t ansmap_size = amp_calc_size(width, height);
    uint8_t *ansmap = malloc(ansmap_size);

    if (!ansmap) {
        static const char message[] = "malloc: allocation failed\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    struct amp_type amp;

    if (amp_init(&amp, width, height, ansmap, ansmap_size) > ansmap_size) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    draw_palette(&amp);

    amp_set_palette(&amp, AMP_PAL_24BIT); // Enable the true color mode.
    amp_to_ans(&amp, nullptr, 0); // Write to stdout.
    amp_stdout("\n", 1);

    free(ansmap);

    return EXIT_SUCCESS;
}

static void draw_palette(struct amp_type *amp) {
    const uint32_t width = amp->width;
    const uint32_t height = amp->height;

    struct amp_rgb_type peaks[] = {
        {   .r  = 255,  .g  =   0,  .b  =   0   },
        {   .r  = 255,  .g  = 255,  .b  =   0   },
        {   .r  =   0,  .g  = 255,  .b  =   0   },
        {   .r  =   0,  .g  = 255,  .b  = 255   },
        {   .r  =   0,  .g  =   0,  .b  = 255   },
        {   .r  = 255,  .g  =   0,  .b  = 255   }
    };

    struct amp_rgb_type rows[height] = {};

    double band = (
        (double) (sizeof(rows)/sizeof(rows[0]))
    ) / (
        (double) (sizeof(peaks)/sizeof(peaks[0]))
    );

    for (size_t i=0; i<sizeof(rows)/sizeof(rows[0]); ++i) {
        double p = (fmod((double) i, band)) / band;
        size_t prev_peak = (size_t) ((double) i / band);
        size_t next_peak = (prev_peak + 1);

         prev_peak %= (sizeof(peaks)/sizeof(peaks[0]));
         next_peak %= (sizeof(peaks)/sizeof(peaks[0]));

        long r = (long) (
            (peaks[next_peak].r * p) + (peaks[prev_peak].r * (1.0 - p))
        );

        long g = (long) (
            (peaks[next_peak].g * p) + (peaks[prev_peak].g * (1.0 - p))
        );

        long b = (long) (
            (peaks[next_peak].b * p) + (peaks[prev_peak].b * (1.0 - p))
        );

        rows[i].r = r < 0 ? 0 : r > UINT8_MAX ? 255 : (uint8_t) r;
        rows[i].g = g < 0 ? 0 : g > UINT8_MAX ? 255 : (uint8_t) g;
        rows[i].b = b < 0 ? 0 : b > UINT8_MAX ? 255 : (uint8_t) b;
    }

    for (unsigned y = 0; y < sizeof(rows)/sizeof(rows[0]); ++y) {
        for (unsigned x = 0; x < width; ++x) {
            long r = 0;
            long g = 0;
            long b = 0;

            if (x < width/2) {
                double p = ((double) x) / (width / 2);

                r = (long) (rows[y].r * p);
                g = (long) (rows[y].g * p);
                b = (long) (rows[y].b * p);
            }
            else {
                double p = ((double) (x - width/2)) / (width/2);

                r = (long) (rows[y].r * (1.0 - p) + p * 255);
                g = (long) (rows[y].g * (1.0 - p) + p * 255);
                b = (long) (rows[y].b * (1.0 - p) + p * 255);
            }

            amp_set_bg_color(
                amp,
                amp_map_rgb(
                    r < 0 ? 0 : r > UINT8_MAX ? 255 : (uint8_t) r,
                    g < 0 ? 0 : g > UINT8_MAX ? 255 : (uint8_t) g,
                    b < 0 ? 0 : b > UINT8_MAX ? 255 : (uint8_t) b
                ), x, y
            );
        }
    }
}
