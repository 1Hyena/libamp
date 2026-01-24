// SPDX-License-Identifier: MIT
#include "../../amp.h"


const uint8_t input_data[] = {
    #embed "../exserialize.amp" if_empty('M', 'i', 's', 's', 'i', 'n', 'g')
};


int main(int, char **) {
    uint32_t width, height;
    size_t data_size = amp_parse_size(
        (const char *) input_data, sizeof(input_data), &width, &height
    );

    if (!data_size) {
        static const char message[] = "amp_parse_size: parse error\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    uint8_t *data = malloc(data_size);

    if (!data) {
        static const char message[] = "malloc: allocation failed\n";
        write(2, message, strlen(message));
        return EXIT_FAILURE;
    }

    struct amp_type amp;

    if (amp_init(&amp, width, height, data, data_size) > data_size) {
        static const char message[] = "amp_init: not enough memory provided\n";
        write(2, message, strlen(message));
        free(data);
        return EXIT_FAILURE;
    }

    if (amp_deserialize(&amp, input_data, sizeof(input_data)) > data_size) {
        static const char message[] = "amp_deserialize: not enough memory\n";
        write(2, message, strlen(message));
        free(data);
        return EXIT_FAILURE;
    }

    amp_to_ans(&amp, nullptr, 0);
    amp_stdout("\n", 1);

    free(data);
    return EXIT_SUCCESS;
}
