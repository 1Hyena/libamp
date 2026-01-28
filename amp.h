// SPDX-License-Identifier: MIT
////////////////////////////////////////////////////////////////////////////////
// MIT License                                                                //
//                                                                            //
// Copyright (c) 2026 Erich Erstu                                             //
//                                                                            //
// Permission is hereby granted, free of charge, to any person obtaining a    //
// copy of this software and associated documentation files (the "Software"), //
// to deal in the Software without restriction, including without limitation  //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   //
// and/or sell copies of the Software, and to permit persons to whom the      //
// Software is furnished to do so, subject to the following conditions:       //
//                                                                            //
// The above copyright notice and this permission notice shall be included in //
// all copies or substantial portions of the Software.                        //
//                                                                            //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        //
// DEALINGS IN THE SOFTWARE.                                                  //
////////////////////////////////////////////////////////////////////////////////

#ifndef AMP_H_12_01_2026
#define AMP_H_12_01_2026
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <string.h>
#include <stdckdint.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbit.h>
////////////////////////////////////////////////////////////////////////////////

#define AMP_MAJOR_VERSION  1
#define AMP_MINOR_VERSION  0
#define AMP_REVISION       0
#define AMP_VERSION        "0.5.0"

#ifndef AMP_BUF_SIZE
#define AMP_BUF_SIZE sizeof(size_t)
#endif

#define AMP_ESC "\x1b"

struct amp_type;

static constexpr size_t AMP_CELL_GLYPH_SIZE = 5; // 4 bytes for UTF8 + null byte
static constexpr size_t AMP_CELL_MODE_SIZE  = 8;
static constexpr size_t AMP_CELL_SIZE       = (
    AMP_CELL_GLYPH_SIZE + AMP_CELL_MODE_SIZE
);

typedef enum : uint8_t {
    AMP_COLOR_NONE = 0,
    ////////////////////////////////////////////////////////////////////////////
    AMP_DARK,       AMP_MAROON,     AMP_GREEN,      AMP_OLIVE,      AMP_NAVY,
    AMP_PURPLE,     AMP_TEAL,       AMP_SILVER,     AMP_CHARCOAL,   AMP_RED,
    AMP_LIME,       AMP_YELLOW,     AMP_BLUE,       AMP_FUCHSIA,    AMP_AQUA,
    AMP_WHITE,
    ////////////////////////////////////////////////////////////////////////////
    AMP_MAX_COLOR
} AMP_COLOR;

struct amp_rgb_type {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef enum : uint64_t {
    AMP_STYLE_NONE      = 0,
    ////////////////////////////////////////////////////////////////////////////
    AMP_HIDDEN          = (1ULL <<  0), AMP_FAINT           = (1ULL <<  1),
    AMP_ITALIC          = (1ULL <<  2), AMP_UNDERLINE       = (1ULL <<  3),
    AMP_BLINKING        = (1ULL <<  4), AMP_STRIKETHROUGH   = (1ULL <<  5),
    ////////////////////////////////////////////////////////////////////////////
    AMP_FG_NONE         = (1ULL <<  6), AMP_FG_DARK         = (1ULL <<  7),
    AMP_FG_MAROON       = (1ULL <<  8), AMP_FG_GREEN        = (1ULL <<  9),
    AMP_FG_OLIVE        = (1ULL << 10), AMP_FG_NAVY         = (1ULL << 11),
    AMP_FG_PURPLE       = (1ULL << 12), AMP_FG_TEAL         = (1ULL << 13),
    AMP_FG_SILVER       = (1ULL << 14), AMP_FG_CHARCOAL     = (1ULL << 15),
    AMP_FG_RED          = (1ULL << 16), AMP_FG_LIME         = (1ULL << 17),
    AMP_FG_YELLOW       = (1ULL << 18), AMP_FG_BLUE         = (1ULL << 19),
    AMP_FG_FUCHSIA      = (1ULL << 20), AMP_FG_AQUA         = (1ULL << 21),
    AMP_FG_WHITE        = (1ULL << 22),
    ////////////////////////////////////////////////////////////////////////////
    AMP_BG_NONE         = (1ULL << 24), AMP_BG_DARK         = (1ULL << 25),
    AMP_BG_MAROON       = (1ULL << 26), AMP_BG_GREEN        = (1ULL << 27),
    AMP_BG_OLIVE        = (1ULL << 28), AMP_BG_NAVY         = (1ULL << 29),
    AMP_BG_PURPLE       = (1ULL << 30), AMP_BG_TEAL         = (1ULL << 31),
    AMP_BG_SILVER       = (1ULL << 32), AMP_BG_CHARCOAL     = (1ULL << 33),
    AMP_BG_RED          = (1ULL << 34), AMP_BG_LIME         = (1ULL << 35),
    AMP_BG_YELLOW       = (1ULL << 36), AMP_BG_BLUE         = (1ULL << 37),
    AMP_BG_FUCHSIA      = (1ULL << 38), AMP_BG_AQUA         = (1ULL << 39),
    AMP_BG_WHITE        = (1ULL << 40),
    ////////////////////////////////////////////////////////////////////////////
    AMP_SOFT_RESET      = (1ULL << 42), AMP_HARD_RESET      = (1ULL << 43)
} AMP_STYLE;

typedef enum : uint8_t {
    AMP_PAL_RGB16 = 0,  // Standard 16 colors (most portable).
    AMP_PAL_24BIT       // True color mode (24 bit color depth).
} AMP_PALETTE;

typedef enum : uint8_t {
    AMP_ALIGN_LEFT = 0,
    AMP_ALIGN_CENTER,
    AMP_ALIGN_RIGHT
} AMP_ALIGN;

typedef enum : uint64_t {
    AMP_SETTINGS_NONE = 0,
    ////////////////////////////////////////////////////////////////////////////
    AMP_DEFLATE = (1ULL <<  0), // Unrequired empty lines are trimmed.
    AMP_FLATTEN = (1ULL <<  1)  // Merge as many style layers as possible.
} AMP_SETTINGS;


// Public API: /////////////////////////////////////////////////////////////////
static inline size_t                    amp_calc_size(
    uint32_t                                ansmap_width,
    uint32_t                                ansmap_height

    // Returns the size of the data buffer needed for the initialization of an
    // ansmap with the given resolution.
);

static inline size_t                    amp_init(
    struct amp_type *                       ansmap,
    uint32_t                                ansmap_width,
    uint32_t                                ansmap_height,
    void *                                  canvas_data,
    size_t                                  canvas_data_size

    // Initializes the given ansmap data structure. If the canvas data array is
    // not big enough for the image, then the end of the image will be cut off.
    //
    // Returns the size of the data buffer needed for the given resolution.
);

static inline void                      amp_clear(
    struct amp_type *                       ansmap
    // Fills the ansmap with empty string glyphs and resets their style.
);

static inline void                      amp_set_palette(
    struct amp_type *                       ansmap,
    AMP_PALETTE                             palette

    // Sets the color palette for the given ansmap. It is effective only during
    // the conversion of the ansmap into ANSI escape sequences.
);

static inline void                      amp_print_glyph(
    struct amp_type *                       ansmap,
    long                                    glyph_x,
    long                                    glyph_y,
    AMP_STYLE                               glyph_style,
    const char *                            glyph_str

    // Prints a single glyph on the given ansmap.
);

static inline void                      amp_print_line(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str

    // Prints the provided UTF-8 encoded text on the ansmap. Newlines and other
    // non-printable ASCII characters will be replaced by question marks.
);

static inline size_t                    amp_print_text(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str

    // Prints the provided UTF-8 encoded text on the ansmap. This function wraps
    // the line if its width exceeds the maximum allowed width. If the maximum
    // width is zero, then wrapping is disabled.
    //
    // Returns the number of lines printed.
);

static inline ssize_t                   amp_to_ans(
    const struct amp_type *                 ansmap,
    char *                                  ans_dst,
    size_t                                  ans_dst_size

    // Converts the given ansmap into ANSI escape sequences. The escape codes
    // will be copied to the provided data buffer. If the buffer pointer is a
    // null pointer, then the output will be written into the program's standard
    // output.
    //
    // Returns the number of bytes that would have been written if the given
    // buffer was big enough. If the buffer is too small, then its first byte
    // is set to zero. The return value of -1 indicates an error.
);

static inline ssize_t                   amp_row_to_ans(
    const struct amp_type *                 ansmap,
    long                                    row_y,
    char *                                  ans_dst,
    size_t                                  ans_dst_size

    // Converts one row of the given ansmap into ANSI escape sequences. The
    // escape codes will be copied to the provided data buffer. If the buffer
    // pointer is a null pointer, then the output will be written into the
    // program's standard output.
    //
    // Returns the number of bytes that would have been written if the given
    // buffer was big enough. If the buffer is too small, then its first byte
    // is set to zero. The return value of -1 indicates an error.
);

static inline ssize_t                   amp_clip_to_ans(
    const struct amp_type *                 ansmap,
    long                                    clip_x,
    long                                    clip_y,
    uint32_t                                width,
    char *                                  ans_dst,
    size_t                                  ans_dst_size

    // Converts a segment of a single row in the given ansmap into ANSI escape
    // sequences. The escape codes will be copied to the provided data buffer.
    // If the buffer pointer is a null pointer, then the output will be written
    // into the program's standard output.
    //
    // Returns the number of bytes that would have been written if the given
    // buffer was big enough. If the buffer is too small, then its first byte
    // is set to zero. The return value of -1 indicates an error.
);

static inline const char *              amp_get_glyph(
    const struct amp_type *                 ansmap,
    long                                    glyph_x,
    long                                    glyph_y

    // Returns a pointer to the null-terminated UTF-8 encoded string of the
    // glyph on the given position of the ansmap. If the specified position is
    // not on the ansmap, then a null pointer is returned.
);

static inline const char *              amp_put_glyph(
    struct amp_type *                       ansmap,
    long                                    glyph_x,
    long                                    glyph_y,
    const char *                            glyph

    // Overwrites a single glyph in the ansmap on the given position and returns
    // a pointer to the null-terminated UTF-8 encoded string of the new glyph.
    // If the specified position is not on the ansmap, then a null pointer is
    // returned.
);

static inline AMP_STYLE                 amp_get_style(
    const struct amp_type *                 ansmap,
    long                                    style_x,
    long                                    style_y

    // Returns the style bits of a glyph on the ansmap from the given position.
);

static inline bool                      amp_put_style(
    struct amp_type *                       ansmap,
    long                                    style_x,
    long                                    style_y,
    AMP_STYLE                               style

    // Sets the style of a glyph on the ansmap at the given position.
    //
    // Returns true on success and false if the position is not on the ansmap.
);

static inline struct amp_rgb_type       amp_get_bg_color(
    struct amp_type *                       ansmap,
    long                                    cell_x,
    long                                    cell_y

    // Returns a color data structure holding the background color information
    // of a glyph on the ansmap at the given position.
);

static inline bool                      amp_set_bg_color(
    struct amp_type *                       ansmap,
    long                                    cell_x,
    long                                    cell_y,
    struct amp_rgb_type                     background_color

    // Sets the background color of a glyph on the ansmap at the given position.
    //
    // Returns true on success and false if the position is not on the ansmap.
);

static inline struct amp_rgb_type       amp_get_fg_color(
    struct amp_type *                       ansmap,
    long                                    cell_x,
    long                                    cell_y

    // Returns a color data structure holding the foreground color information
    // of a glyph on the ansmap at the given position.
);

static inline bool                      amp_set_fg_color(
    struct amp_type *                       ansmap,
    long                                    cell_x,
    long                                    cell_y,
    struct amp_rgb_type                     foreground_color

    // Sets the foreground color of a glyph on the ansmap at the given position.
    //
    // Returns true on success and false if the position is not on the ansmap.
);

static inline struct amp_rgb_type       amp_map_rgb(
    uint8_t                                 red,
    uint8_t                                 green,
    uint8_t                                 blue

    // Returns a color data structure holding the color information given in
    // the arguments.
);

static inline void                      amp_unmap_rgb(
    struct amp_rgb_type                     color,
    uint8_t *                               red,
    uint8_t *                               green,
    uint8_t *                               blue

    // Copies the red, green and blue color components from the given color data
    // structure to the addresses specified in the arguments respectively.
);

static inline struct amp_color_type     amp_lookup_color(
    AMP_COLOR                               color_index

    // Returns a color data structure holding the color information of the given
    // color by its index.
);

static inline ssize_t                   amp_stdout(
    const char *                            str_src,
    size_t                                  str_src_size

    // Writes the given buffer into the program's standard output fully.
    //
    // Returns the number of bytes written or -1 to indicate an error.
);

static inline size_t                    amp_print_rich_text(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str

    // Prints the provided UTF-8 encoded rich text on the ansmap. Inline
    // embedded style markers are applied to the text as it is printed. This
    // function wraps the line if its width exceeds the maximum allowed width.
    // If the maximum width is zero, then wrapping is disabled.
    //
    // Returns the number of lines printed.
);

static inline uint32_t                  amp_get_width(
    const struct amp_type *                 ansmap
    // Returns the width of the given ansmap image.
);

static inline uint32_t                  amp_get_height(
    const struct amp_type *                 ansmap
    // Returns the height of the given ansmap image.
);

static inline AMP_PALETTE               amp_get_palette(
    const struct amp_type *                 ansmap
    // Returns the palette of the given ansmap image.
);

static inline ssize_t                   amp_snprint_textf(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    char *                                  text_format_buffer,
    size_t                                  text_format_buffer_size,
    const char *                            text_format,
                                            ...

    // Prints the provided UTF-8 encoded formatted text on the ansmap. This
    // function wraps the line if its width exceeds the maximum allowed width.
    // If the maximum width is zero, then wrapping is disabled. If the provided
    // text format buffer could not fit the text after formatting or if an error
    // occurred during formatting, then nothing is printed on the ansmap.
    //
    // Returns the number of bytes that would have been written into the text
    // format buffer (excluding the null byte used to end output to strings).
    // The return value of -1 indicates that an output error was encountered in
    // the underlying call to vsnprintf.
) __attribute__((format (printf, 9, 10)));

static inline ssize_t                   amp_snprint_rich_textf(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    char *                                  text_format_buffer,
    size_t                                  text_format_buffer_size,
    const char *                            text_format,
                                            ...

    // Prints the provided UTF-8 encoded formatted text on the ansmap. Inline
    // embedded style markers are applied to the text as it is printed. This
    // function wraps the line if its width exceeds the maximum allowed width.
    // If the maximum width is zero, then wrapping is disabled. If the provided
    // text format buffer could not fit the text after formatting or if an error
    // occurred during formatting, then nothing is printed on the ansmap.
    //
    // Returns the number of bytes that would have been written into the text
    // format buffer (excluding the null byte used to end output to strings).
    // The return value of -1 indicates that an output error was encountered in
    // the underlying call to vsnprintf.
) __attribute__((format (printf, 9, 10)));

static inline ssize_t                   amp_snprint_linef(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    AMP_ALIGN                               text_alignment,
    char *                                  text_format_buffer,
    size_t                                  text_format_buffer_size,
    const char *                            text_format,
                                            ...

    // Prints the provided UTF-8 encoded formatted text on the ansmap. Newlines
    // and other non-printable ASCII characters will be replaced by question
    // marks. If the provided text format buffer could not fit the text after
    // formatting or if an error occurred during formatting, then nothing is
    // printed on the ansmap.
    //
    // Returns the number of bytes that would have been written into the text
    // format buffer (excluding the null byte used to end output to strings).
    // The return value of -1 indicates that an output error was encountered in
    // the underlying call to vsnprintf.
) __attribute__((format (printf, 8, 9)));

static inline ssize_t                   amp_encode(
    const struct amp_type *                 ansmap,
    AMP_SETTINGS                            flags,
    char *                                  buffer,
    size_t                                  buffer_size

    // Exports the specified ansmap as a human-readable plaintext document. The
    // file content is written into the provided buffer, given that the buffer
    // is large enough for complete storage. If the buffer pointer is a null
    // pointer, then the output will be written into the program's standard
    // output.
    //
    // AMP_SETTINGS flags:
    //   * AMP_DEFLATE - Unrequired empty lines are trimmed.
    //   * AMP_FLATTEN - Merge as many style layers as possible.
    //
    // Returns the number of bytes that was written or would have been written
    // (excluding the null byte used to end output to strings). If the buffer is
    // too small, then its first byte is set to zero. The return value of -1
    // indicates an error.
);

static inline size_t                    amp_doc_parse_size(
    const void *                            doc_data,
    size_t                                  doc_data_size,
    uint32_t *                              amp_width,
    uint32_t *                              amp_height

    // Parses the provided data as an AMP document and attempts to determine the
    // size of a buffer required for the deserialization of the document. If the
    // size was found, then the width and height of the parsed ansmap are
    // written to the memory addresses specified by the width and height pointer
    // arguments respectively.
    //
    // Returns the size of the buffer required for ansmap decoding. The return
    // value of zero indicates a parsing error.
);

static inline size_t                    amp_decode(
    struct amp_type *                       ansmap,
    const void *                            data,
    size_t                                  data_size

    // Imports a human-readable plaintext document from the data array into the
    // referenced ansmap. If the ansmap could not fit the image, then the image
    // will be cropped to fit.
    //
    // Returns the original canvas size of the decoded ansmap. The return
    // value of zero indicates a parsing error.
);

static inline void                      amp_draw_ansmap(
    struct amp_type *                       dst_ansmap,
    long                                    x_on_dst_ansmap,
    long                                    y_on_dst_ansmap,
    const struct amp_type *                 src_ansmap

    // Draws a copy of the source ansmap onto the destination ansmap at the
    // specified position. It uses a masked drawing mode where transparent cells
    // are skipped, so the background image will show through the masked parts
    // of the source image. Transparent cells are marked by their glyphs
    // containing either a space or an empty string, having no style specified.
);
////////////////////////////////////////////////////////////////////////////////


struct amp_type {
    uint8_t buffer[AMP_BUF_SIZE];
    uint32_t width;
    uint32_t height;

    struct {
        size_t size;
        uint8_t *data;

        struct {
            size_t size;
            uint8_t *data;
        } glyph;

        struct {
            size_t size;
            uint8_t *data;
        } mode;
    } canvas;

    AMP_PALETTE palette;
};

struct amp_mode_type {
    struct amp_rgb_type fg;
    struct amp_rgb_type bg;

    struct {
        bool fg:1;
        bool bg:1;
        bool hidden:1;
        bool faint:1;
        bool italic:1;
        bool underline:1;
        bool blinking:1;
        bool strikethrough:1;

        // not serialized:
        bool broken:1;
        bool reset:1;
    } bitset;
};

struct amp_mode_code_type {
    struct {
        uint8_t data[8]; // 6 for decoration + inverse and bold
        uint8_t size;
    } style;

    struct {
        struct {
            uint8_t data[5];
            uint8_t size;
        } fg;

        struct {
            uint8_t data[5];
            uint8_t size;
        } bg;
    } color;

    struct {
        bool reset:1; // used when returning mode updates
    } bitset;
};

struct amp_style_flag_type {
    char        glyph[AMP_CELL_GLYPH_SIZE];
    AMP_STYLE   value;
};

struct amp_color_combo_type {
    AMP_COLOR colors[5];
};

// Private API: ////////////////////////////////////////////////////////////////
static inline ssize_t                   amp_copy_glyph(
    const struct amp_type *                 ansmap,
    long                                    x,
    long                                    y,
    uint8_t *                               glyph_dst,
    size_t                                  glyph_dst_size
);
static inline bool                      amp_set_mode(
    struct amp_type *                       ansmap,
    long                                    x,
    long                                    y,
    struct amp_mode_type                    mode
);
static inline struct amp_mode_type      amp_get_mode(
    const struct amp_type *                 ansmap,
    long                                    x,
    long                                    y
);
static inline uint8_t *                 amp_get_mode_data(
    const struct amp_type *                 amp,
    long                                    x,
    long                                    y
);
static inline ssize_t                   amp_get_cell_index(
    const struct amp_type *                 ansmap,
    long                                    x,
    long                                    y
);
static inline int                       amp_utf8_code_point_size(
    const char *                            utf8_str,
    size_t                                  utf8_str_size
);
static inline size_t                    amp_utf8_code_point_count(
    const char *                            utf8_str,
    size_t                                  utf8_str_size
);
static inline size_t                    amp_str_seg_style_sign_count(
    const char *                            str,
    size_t                                  str_size
);
static inline struct amp_mode_code_type amp_mode_to_codes(
    struct amp_mode_type                    mode,
    AMP_PALETTE                             palette
);
static inline struct amp_mode_code_type amp_mode_code_update(
    struct amp_mode_code_type               next_codes,
    struct amp_mode_code_type               prev_codes
);
static inline struct amp_mode_type     amp_mode_cell_deserialize(
    const uint8_t *                         src,
    size_t                                  src_size
);
static inline bool                      amp_mode_cell_serialize(
    struct amp_mode_type                    mode,
    uint8_t *                               dst,
    size_t                                  dst_size
);
static inline size_t                    amp_sub_size(
    size_t                                  a,
    size_t                                  b
);
static inline size_t                    amp_str_append(
    char *                                  str_dst,
    size_t                                  str_dst_size,
    const char *                            str_src
);
static inline struct amp_color_type     amp_find_color(
    struct amp_rgb_type                     rgb
);
static inline const char *              amp_str_seg_first_line_size(
    const char *                            str,
    size_t                                  str_size,
    size_t *                                line_size
);
static inline const char *              amp_str_seg_skip_any_utf8_symbol(
    const char *                            str,
    size_t                                  str_size
);
static inline const char *              amp_str_seg_skip_str(
    const char *                            str_seg,
    size_t                                  str_seg_size,
    const char *                            str
);
static inline size_t                    amp_str_seg_width(
    const char *                            str,
    size_t                                  str_size
);
static inline size_t                    amp_rich_str_seg_width(
    const char *                            rich_str,
    size_t                                  rich_str_size
);
static inline void                      amp_print_line_clip(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str,
    size_t                                  text_str_size
);
static inline void                      amp_print_rich_line_clip(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE *                             text_style,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str,
    size_t                                  text_str_size
);
static inline size_t                    amp_print_text_clip(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE                               text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str,
    size_t                                  text_str_size
);
static inline size_t                    amp_print_rich_text_clip(
    struct amp_type *                       ansmap,
    long                                    text_x,
    long                                    text_y,
    AMP_STYLE *                             text_style,
    uint32_t                                text_max_width,
    AMP_ALIGN                               text_alignment,
    const char *                            text_str,
    size_t                                  text_str_size
);
static inline const char *              amp_str_seg_skip_spaces(
    const char *                            str,
    size_t                                  str_size
);
static inline const char *              amp_str_seg_skip_wrap(
    const char *                            str,
    size_t                                  str_size,
    size_t                                  wrap_width
);
static inline const char *              amp_rich_str_seg_skip_wrap(
    const char *                            rich_str,
    size_t                                  rich_str_size,
    size_t                                  wrap_width
);
static inline const char *              amp_str_seg_skip_word(
    const char *                            str,
    size_t                                  str_size
);
static inline const char *              amp_str_seg_skip_width(
    const char *                            str,
    size_t                                  str_size,
    size_t                                  max_width
);
static inline const char *              amp_str_seg_skip_style_sign(
    const char *                            str,
    size_t                                  str_sz
);
static inline const char *              amp_str_seg_skip_style_and_spaces(
    const char *                            str,
    size_t                                  str_sz
);
static inline const char *              amp_str_seg_skip_style_and_word(
    const char *                            str,
    size_t                                  str_sz
);
static inline const char *              amp_str_seg_skip_styles(
    const char *                            str,
    size_t                                  str_sz
);
static inline const char *              amp_str_seg_skip_style_and_utf8_symbol(
    const char *                            str,
    size_t                                  str_sz
);
static inline
struct amp_inline_style_type            amp_lookup_inline_style(
    const char *                            glyph
);
static inline
struct amp_style_flag_type              amp_lookup_style_flag(
    AMP_STYLE
);
static inline
struct amp_color_combo_type             amp_lookup_color_combo(
    struct amp_rgb_type                     rgb
);
static inline ssize_t                   amp_encode_layer(
    const struct amp_type *                 ansmap,
    AMP_SETTINGS                            settings,
    AMP_STYLE                               style,
    char *                                  buffer,
    size_t                                  buffer_size
);
static inline ssize_t                   amp_encode_layer_row(
    const struct amp_type *                 ansmap,
    long                                    row_y,
    AMP_STYLE                               style,
    char *                                  buffer,
    size_t                                  buffer_size
);
static inline ssize_t                   amp_encode_layer_cell(
    const struct amp_type *                 ansmap,
    long                                    x,
    long                                    y,
    AMP_STYLE                               style,
    char *                                  buffer,
    size_t                                  buffer_size
);
static inline AMP_STYLE                 amp_styles_to_layer(
    const struct amp_type *                 ansmap,
    AMP_STYLE                               whitelist
);
static inline uint32_t                  amp_doc_seg_parse_width(
    const char *                            str,
    size_t                                  str_sz
);
static inline size_t                    amp_decode_glyphs(
    struct amp_type *                       amp,
    const char *                            str,
    size_t                                  str_sz
);
static inline size_t                    amp_decode_styles(
    struct amp_type *                       amp,
    const char *                            str,
    size_t                                  str_sz
);
////////////////////////////////////////////////////////////////////////////////


// AMP_FLAG_INDEX is a constant expression that determines the index of a single
// one-bit in the unsigned integer argument a. It is based on binary search and
// is 50% slower than the stdc_first_trailing_one_ull function (stdbit.h).
#define AMP_FLAG_INDEX(a) (                                                    \
    (a) < (1ULL << 32) ? (                                                     \
        (a) < (1ULL << 16) ? (                                                 \
            (a) < (1ULL << 8) ? (                                              \
                (a) < (1ULL << 4) ? (                                          \
                    (a) < (1ULL << 2) ? (                                      \
                        (a) < (1ULL << 1) ? (                                  \
                            (a) == (1ULL << 0) ? (1) : (0)                     \
                        ) : (                                                  \
                            (a) == (1ULL << 1) ? (2) : (0)                     \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 3) ? (                                  \
                            (a) == (1ULL << 2) ? (3) : (0)                     \
                        ) : (                                                  \
                            (a) == (1ULL << 3) ? (4) : (0)                     \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 6) ? (                                      \
                        (a) < (1ULL << 5) ? (                                  \
                            (a) == (1ULL << 4) ? (5) : (0)                     \
                        ) : (                                                  \
                            (a) == (1ULL << 5) ? (6) : (0)                     \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 7) ? (                                  \
                            (a) == (1ULL << 6) ? (7) : (0)                     \
                        ) : (                                                  \
                            (a) == (1ULL << 7) ? (8) : (0)                     \
                        )                                                      \
                    )                                                          \
                )                                                              \
            ) : (                                                              \
                (a) < (1ULL << 12) ? (                                         \
                    (a) < (1ULL << 10) ? (                                     \
                        (a) < (1ULL << 9) ? (                                  \
                            (a) == (1ULL << 8) ? (9) : (0)                     \
                        ) : (                                                  \
                            (a) == (1ULL << 9) ? (10) : (0)                    \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 11) ? (                                 \
                            (a) == (1ULL << 10) ? (11) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 11) ? (12) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 14) ? (                                     \
                        (a) < (1ULL << 13) ? (                                 \
                            (a) == (1ULL << 12) ? (13) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 13) ? (14) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 15) ? (                                 \
                            (a) == (1ULL << 14) ? (15) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 15) ? (16) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            )                                                                  \
        ) : (                                                                  \
            (a) < (1ULL << 24) ? (                                             \
                (a) < (1ULL << 20) ? (                                         \
                    (a) < (1ULL << 18) ? (                                     \
                        (a) < (1ULL << 17) ? (                                 \
                            (a) == (1ULL << 16) ? (17) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 17) ? (18) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 19) ? (                                 \
                            (a) == (1ULL << 18) ? (19) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 19) ? (20) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 22) ? (                                     \
                        (a) < (1ULL << 21) ? (                                 \
                            (a) == (1ULL << 20) ? (21) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 21) ? (22) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 23) ? (                                 \
                            (a) == (1ULL << 22) ? (23) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 23) ? (24) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            ) : (                                                              \
                (a) < (1ULL << 28) ? (                                         \
                    (a) < (1ULL << 26) ? (                                     \
                        (a) < (1ULL << 25) ? (                                 \
                            (a) == (1ULL << 24) ? (25) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 25) ? (26) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 27) ? (                                 \
                            (a) == (1ULL << 26) ? (27) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 27) ? (28) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 30) ? (                                     \
                        (a) < (1ULL << 29) ? (                                 \
                            (a) == (1ULL << 28) ? (29) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 29) ? (30) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 31) ? (                                 \
                            (a) == (1ULL << 30) ? (31) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 31) ? (32) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            )                                                                  \
        )                                                                      \
    ) : (                                                                      \
        (a) < (1ULL << 48) ? (                                                 \
            (a) < (1ULL << 40) ? (                                             \
                (a) < (1ULL << 36) ? (                                         \
                    (a) < (1ULL << 34) ? (                                     \
                        (a) < (1ULL << 33) ? (                                 \
                            (a) == (1ULL << 32) ? (33) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 33) ? (34) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 35) ? (                                 \
                            (a) == (1ULL << 34) ? (35) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 35) ? (36) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 38) ? (                                     \
                        (a) < (1ULL << 37) ? (                                 \
                            (a) == (1ULL << 36) ? (37) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 37) ? (38) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 39) ? (                                 \
                            (a) == (1ULL << 38) ? (39) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 39) ? (40) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            ) : (                                                              \
                (a) < (1ULL << 44) ? (                                         \
                    (a) < (1ULL << 42) ? (                                     \
                        (a) < (1ULL << 41) ? (                                 \
                            (a) == (1ULL << 40) ? (41) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 41) ? (42) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 43) ? (                                 \
                            (a) == (1ULL << 42) ? (43) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 43) ? (44) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 46) ? (                                     \
                        (a) < (1ULL << 45) ? (                                 \
                            (a) == (1ULL << 44) ? (45) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 45) ? (46) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 47) ? (                                 \
                            (a) == (1ULL << 46) ? (47) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 47) ? (48) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            )                                                                  \
        ) : (                                                                  \
            (a) < (1ULL << 56) ? (                                             \
                (a) < (1ULL << 52) ? (                                         \
                    (a) < (1ULL << 50) ? (                                     \
                        (a) < (1ULL << 49) ? (                                 \
                            (a) == (1ULL << 48) ? (49) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 49) ? (50) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 51) ? (                                 \
                            (a) == (1ULL << 50) ? (51) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 51) ? (52) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 54) ? (                                     \
                        (a) < (1ULL << 53) ? (                                 \
                            (a) == (1ULL << 52) ? (53) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 53) ? (54) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 55) ? (                                 \
                            (a) == (1ULL << 54) ? (55) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 55) ? (56) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            ) : (                                                              \
                (a) < (1ULL << 60) ? (                                         \
                    (a) < (1ULL << 58) ? (                                     \
                        (a) < (1ULL << 57) ? (                                 \
                            (a) == (1ULL << 56) ? (57) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 57) ? (58) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 59) ? (                                 \
                            (a) == (1ULL << 58) ? (59) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 59) ? (60) : (0)                   \
                        )                                                      \
                    )                                                          \
                ) : (                                                          \
                    (a) < (1ULL << 62) ? (                                     \
                        (a) < (1ULL << 61) ? (                                 \
                            (a) == (1ULL << 60) ? (61) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 61) ? (62) : (0)                   \
                        )                                                      \
                    ) : (                                                      \
                        (a) < (1ULL << 63) ? (                                 \
                            (a) == (1ULL << 62) ? (63) : (0)                   \
                        ) : (                                                  \
                            (a) == (1ULL << 63) ? (64) : (0)                   \
                        )                                                      \
                    )                                                          \
                )                                                              \
            )                                                                  \
        )                                                                      \
    )                                                                          \
)

static const struct amp_style_flag_type amp_style_flag_table[] = {
    [AMP_FLAG_INDEX(AMP_STYLE_NONE)] = {
        .value  = AMP_STYLE_NONE,           .glyph = ""
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_FLAG_INDEX(AMP_HIDDEN)] = {
        .value  = AMP_HIDDEN,               .glyph = "#"
    },
    [AMP_FLAG_INDEX(AMP_FAINT)] = {
        .value  = AMP_FAINT,                .glyph = "?"
    },
    [AMP_FLAG_INDEX(AMP_ITALIC)] = {
        .value  = AMP_ITALIC,               .glyph = "/"
    },
    [AMP_FLAG_INDEX(AMP_UNDERLINE)] = {
        .value  = AMP_UNDERLINE,            .glyph = "_"
    },
    [AMP_FLAG_INDEX(AMP_BLINKING)] = {
        .value  = AMP_BLINKING,             .glyph = "*"
    },
    [AMP_FLAG_INDEX(AMP_STRIKETHROUGH)] = {
        .value  = AMP_STRIKETHROUGH,        .glyph = "-"
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_FLAG_INDEX(AMP_FG_NONE)] = {
        .value  = AMP_FG_NONE,              .glyph = ""
    },
    [AMP_FLAG_INDEX(AMP_FG_DARK)] = {
        .value  = AMP_FG_DARK,              .glyph = "d"
    },
    [AMP_FLAG_INDEX(AMP_FG_MAROON)] = {
        .value  = AMP_FG_MAROON,            .glyph = "m"
    },
    [AMP_FLAG_INDEX(AMP_FG_GREEN)] = {
        .value  = AMP_FG_GREEN,             .glyph = "g"
    },
    [AMP_FLAG_INDEX(AMP_FG_OLIVE)] = {
        .value  = AMP_FG_OLIVE,             .glyph = "o"
    },
    [AMP_FLAG_INDEX(AMP_FG_NAVY)] = {
        .value  = AMP_FG_NAVY,              .glyph = "n"
    },
    [AMP_FLAG_INDEX(AMP_FG_PURPLE)] = {
        .value  = AMP_FG_PURPLE,            .glyph = "p"
    },
    [AMP_FLAG_INDEX(AMP_FG_TEAL)] = {
        .value  = AMP_FG_TEAL,              .glyph = "t"
    },
    [AMP_FLAG_INDEX(AMP_FG_SILVER)] = {
        .value  = AMP_FG_SILVER,            .glyph = "s"
    },
    [AMP_FLAG_INDEX(AMP_FG_CHARCOAL)] = {
        .value  = AMP_FG_CHARCOAL,          .glyph = "c"
    },
    [AMP_FLAG_INDEX(AMP_FG_RED)] = {
        .value  = AMP_FG_RED,               .glyph = "r"
    },
    [AMP_FLAG_INDEX(AMP_FG_LIME)] = {
        .value  = AMP_FG_LIME,              .glyph = "l"
    },
    [AMP_FLAG_INDEX(AMP_FG_YELLOW)] = {
        .value  = AMP_FG_YELLOW,            .glyph = "y"
    },
    [AMP_FLAG_INDEX(AMP_FG_BLUE)] = {
        .value  = AMP_FG_BLUE,              .glyph = "b"
    },
    [AMP_FLAG_INDEX(AMP_FG_FUCHSIA)] = {
        .value  = AMP_FG_FUCHSIA,           .glyph = "f"
    },
    [AMP_FLAG_INDEX(AMP_FG_AQUA)] = {
        .value  = AMP_FG_AQUA,              .glyph = "a"
    },
    [AMP_FLAG_INDEX(AMP_FG_WHITE)] = {
        .value  = AMP_FG_WHITE,             .glyph = "w"
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_FLAG_INDEX(AMP_BG_NONE)] = {
        .value  = AMP_BG_NONE,              .glyph = ""
    },
    [AMP_FLAG_INDEX(AMP_BG_DARK)] = {
        .value  = AMP_BG_DARK,              .glyph = "D"
    },
    [AMP_FLAG_INDEX(AMP_BG_MAROON)] = {
        .value  = AMP_BG_MAROON,            .glyph = "M"
    },
    [AMP_FLAG_INDEX(AMP_BG_GREEN)] = {
        .value  = AMP_BG_GREEN,             .glyph = "G"
    },
    [AMP_FLAG_INDEX(AMP_BG_OLIVE)] = {
        .value  = AMP_BG_OLIVE,             .glyph = "O"
    },
    [AMP_FLAG_INDEX(AMP_BG_NAVY)] = {
        .value  = AMP_BG_NAVY,              .glyph = "N"
    },
    [AMP_FLAG_INDEX(AMP_BG_PURPLE)] = {
        .value  = AMP_BG_PURPLE,            .glyph = "P"
    },
    [AMP_FLAG_INDEX(AMP_BG_TEAL)] = {
        .value  = AMP_BG_TEAL,              .glyph = "T"
    },
    [AMP_FLAG_INDEX(AMP_BG_SILVER)] = {
        .value  = AMP_BG_SILVER,            .glyph = "S"
    },
    [AMP_FLAG_INDEX(AMP_BG_CHARCOAL)] = {
        .value  = AMP_BG_CHARCOAL,          .glyph = "C"
    },
    [AMP_FLAG_INDEX(AMP_BG_RED)] = {
        .value  = AMP_BG_RED,               .glyph = "R"
    },
    [AMP_FLAG_INDEX(AMP_BG_LIME)] = {
        .value  = AMP_BG_LIME,              .glyph = "L"
    },
    [AMP_FLAG_INDEX(AMP_BG_YELLOW)] = {
        .value  = AMP_BG_YELLOW,            .glyph = "Y"
    },
    [AMP_FLAG_INDEX(AMP_BG_BLUE)] = {
        .value  = AMP_BG_BLUE,              .glyph = "B"
    },
    [AMP_FLAG_INDEX(AMP_BG_FUCHSIA)] = {
        .value  = AMP_BG_FUCHSIA,           .glyph = "F"
    },
    [AMP_FLAG_INDEX(AMP_BG_AQUA)] = {
        .value  = AMP_BG_AQUA,              .glyph = "A"
    },
    [AMP_FLAG_INDEX(AMP_BG_WHITE)] = {
        .value  = AMP_BG_WHITE,             .glyph = "W"
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_FLAG_INDEX(AMP_SOFT_RESET)] = {
        .value  = AMP_SOFT_RESET,           .glyph = "x"
    },
    [AMP_FLAG_INDEX(AMP_HARD_RESET)] = {
        .value  = AMP_HARD_RESET,           .glyph = "X"
    }
};

static const struct amp_inline_style_type {
    const char *name;
    const char *glyph;
    AMP_STYLE   style;
} amp_inline_style_table[] = {
    [  0]   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_STYLE_NONE)].glyph,
        .style  = AMP_STYLE_NONE,
        .name   = "none"
    },
    ////////////////////////////////////////////////////////////////////////////
    ['#']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_HIDDEN)].glyph,
        .style  = AMP_HIDDEN,
        .name   = "hidden"
    },
    ['*']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BLINKING)].glyph,
        .style  = AMP_BLINKING,
        .name = "blinking"
    },
    ['-']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_STRIKETHROUGH)].glyph,
        .style  = AMP_STRIKETHROUGH,
        .name = "strikethrough"
    },
    ['/']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_ITALIC)].glyph,
        .style  = AMP_ITALIC,
        .name   = "italic"
    },
    ['?']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FAINT)].glyph,
        .style  = AMP_FAINT,
        .name   = "faint"
    },
    ['A']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_AQUA)].glyph,
        .style  = AMP_BG_AQUA,
        .name   = "aqua background"
    },
    ['B']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_BLUE)].glyph,
        .style  = AMP_BG_BLUE,
        .name   = "blue background"
    },
    ['C']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_CHARCOAL)].glyph,
        .style  = AMP_BG_CHARCOAL,
        .name   = "charcoal background"
    },
    ['D']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_DARK)].glyph,
        .style  = AMP_BG_DARK,
        .name   = "dark background"
    },
    ['F']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_FUCHSIA)].glyph,
        .style  = AMP_BG_FUCHSIA,
        .name   = "fuchsia background"
    },
    ['G']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_GREEN)].glyph,
        .style  = AMP_BG_GREEN,
        .name   = "green background"
    },
    ['L']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_LIME)].glyph,
        .style  = AMP_BG_LIME,
        .name   = "lime background"
    },
    ['M']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_MAROON)].glyph,
        .style  = AMP_BG_MAROON,
        .name   = "maroon background"
    },
    ['N']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_NAVY)].glyph,
        .style  = AMP_BG_NAVY,
        .name   = "navy background"
    },
    ['O']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_OLIVE)].glyph,
        .style  = AMP_BG_OLIVE,
        .name   = "olive background"
    },
    ['P']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_PURPLE)].glyph,
        .style  = AMP_BG_PURPLE,
        .name   = "purple background"
    },
    ['R']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_RED)].glyph,
        .style  = AMP_BG_RED,
        .name   = "red background"
    },
    ['S']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_SILVER)].glyph,
        .style  = AMP_BG_SILVER,
        .name   = "silver background"
    },
    ['T']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_TEAL)].glyph,
        .style  = AMP_BG_TEAL,
        .name   = "teal background"
    },
    ['W']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_WHITE)].glyph,
        .style  = AMP_BG_WHITE,
        .name   = "white background"
    },
    ['X']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_HARD_RESET)].glyph,
        .style  = AMP_HARD_RESET,
        .name   = "reset all"
    },
    ['Y']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_BG_YELLOW)].glyph,
        .style  = AMP_BG_YELLOW,
        .name   = "yellow background"
    },
    ['_']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_UNDERLINE)].glyph,
        .style  = AMP_UNDERLINE,
        .name   = "underline"
    },
    ['a']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_AQUA)].glyph,
        .style  = AMP_FG_AQUA,
        .name   = "aqua foreground"
    },
    ['b']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_BLUE)].glyph,
        .style  = AMP_FG_BLUE,
        .name   = "blue foreground"
    },
    ['c']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_CHARCOAL)].glyph,
        .style  = AMP_FG_CHARCOAL,
        .name   = "charcoal foreground"
    },
    ['d']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_DARK)].glyph,
        .style  = AMP_FG_DARK,
        .name   = "dark foreground"
    },
    ['f']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_FUCHSIA)].glyph,
        .style  = AMP_FG_FUCHSIA,
        .name   = "fuchsia foreground"
    },
    ['g']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_GREEN)].glyph,
        .style  = AMP_FG_GREEN,
        .name   = "green foreground"
    },
    ['l']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_LIME)].glyph,
        .style  = AMP_FG_LIME,
        .name   = "lime foreground"
    },
    ['m']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_MAROON)].glyph,
        .style  = AMP_FG_MAROON,
        .name   = "maroon foreground"
    },
    ['n']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_NAVY)].glyph,
        .style  = AMP_FG_NAVY,
        .name   = "navy foreground"
    },
    ['o']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_OLIVE)].glyph,
        .style  = AMP_FG_OLIVE,
        .name   = "olive foreground"
    },
    ['p']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_PURPLE)].glyph,
        .style  = AMP_FG_PURPLE,
        .name   = "purple foreground"
    },
    ['r']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_RED)].glyph,
        .style  = AMP_FG_RED,
        .name   = "red foreground"
    },
    ['s']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_SILVER)].glyph,
        .style  = AMP_FG_SILVER,
        .name   = "silver foreground"
    },
    ['t']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_TEAL)].glyph,
        .style  = AMP_FG_TEAL,
        .name   = "teal foreground"
    },
    ['w']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_WHITE)].glyph,
        .style  = AMP_FG_WHITE,
        .name   = "white foreground"
    },
    ['x']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_SOFT_RESET)].glyph,
        .style  = AMP_SOFT_RESET,
        .name   = "reset foreground"
    },
    ['y']   = {
        .glyph  = amp_style_flag_table[AMP_FLAG_INDEX(AMP_FG_YELLOW)].glyph,
        .style  = AMP_FG_YELLOW,
        .name   = "yellow foreground"
    },
    ////////////////////////////////////////////////////////////////////////////
    {}
};

static const struct amp_color_type {
    struct {
        AMP_STYLE fg;
        AMP_STYLE bg;
    } style;

    struct amp_rgb_type rgb;

    struct {
        uint8_t fg;
        uint8_t bg;
    } code;

    AMP_COLOR index;
    struct {
        bool bright:1;
    } bitset;
} amp_color_table[] = {
    [AMP_COLOR_NONE] = {
        .index  = AMP_COLOR_NONE,
        .rgb    = {},
        .style  = { .fg = AMP_FG_NONE, .bg = AMP_BG_NONE }
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_DARK] = {
        .index  = AMP_DARK,     .rgb    = { .r  = 0,    .g  = 0,    .b  = 0   },
        .style  = {
            .fg = AMP_FG_DARK,
            .bg = AMP_BG_DARK
        },
        .code   = { .fg = 30, .bg = 40 }
    },
    [AMP_MAROON] = {
        .index  = AMP_MAROON,   .rgb    = { .r  = 128,  .g  = 0,    .b  = 0   },
        .style  = {
            .fg = AMP_FG_MAROON,
            .bg = AMP_BG_MAROON
        },
        .code   = { .fg = 31, .bg = 41 }
    },
    [AMP_GREEN] = {
        .index  = AMP_GREEN,    .rgb    = { .r  = 0,    .g  = 128,  .b  = 0   },
        .style  = {
            .fg = AMP_FG_GREEN,
            .bg = AMP_BG_GREEN
        },
        .code   = { .fg = 32, .bg = 42 }
    },
    [AMP_OLIVE] = {
        .index  = AMP_OLIVE,    .rgb    = { .r  = 128,  .g  = 128,  .b  = 0   },
        .style  = {
            .fg = AMP_FG_OLIVE,
            .bg = AMP_BG_OLIVE
        },
        .code   = { .fg = 33, .bg = 43 }
    },
    [AMP_NAVY] = {
        .index  = AMP_NAVY,     .rgb    = { .r  = 0,    .g  = 0,    .b  = 128 },
        .style  = {
            .fg = AMP_FG_NAVY,
            .bg = AMP_BG_NAVY
        },
        .code   = { .fg = 34, .bg = 44 }
    },
    [AMP_PURPLE] = {
        .index  = AMP_PURPLE,   .rgb    = { .r  = 128,  .g  = 0,    .b  = 128 },
        .style  = {
            .fg = AMP_FG_PURPLE,
            .bg = AMP_BG_PURPLE
        },
        .code   = { .fg = 35, .bg = 45 }
    },
    [AMP_TEAL] = {
        .index  = AMP_TEAL,     .rgb    = { .r  = 0,    .g  = 128,  .b  = 128 },
        .style  = {
            .fg = AMP_FG_TEAL,
            .bg = AMP_BG_TEAL
        },
        .code   = { .fg = 36, .bg = 46 }
    },
    [AMP_SILVER] = {
        .index  = AMP_SILVER,   .rgb    = { .r  = 192,  .g  = 192,  .b  = 192 },
        .style  = {
            .fg = AMP_FG_SILVER,
            .bg = AMP_BG_SILVER
        },
        .code   = { .fg = 37, .bg = 47 }
    },
    [AMP_CHARCOAL] = {
        .index  = AMP_CHARCOAL, .rgb    = { .r  = 128,  .g  = 128,   .b = 128 },
        .style  = {
            .fg = AMP_FG_CHARCOAL,
            .bg = AMP_BG_CHARCOAL
        },
        .code   = { .fg = 30, .bg = 40 },
        .bitset = { .bright = true }
    },
    [AMP_RED] = {
        .index  = AMP_RED,      .rgb    = { .r  = 255,  .g  = 0,    .b  = 0   },
        .style  = {
            .fg = AMP_FG_RED,
            .bg = AMP_BG_RED
        },
        .code   = { .fg = 31, .bg = 41 },
        .bitset = { .bright = true }
    },
    [AMP_LIME] = {
        .index  = AMP_LIME,     .rgb    = { .r  = 0,    .g  = 255,  .b  = 0   },
        .style  = {
            .fg = AMP_FG_LIME,
            .bg = AMP_BG_LIME
        },
        .code   = { .fg = 32, .bg = 42 },
        .bitset = { .bright = true }
    },
    [AMP_YELLOW] = {
        .index  = AMP_YELLOW,   .rgb    = { .r  = 255,  .g  = 255,  .b  = 0   },
        .style  = {
            .fg = AMP_FG_YELLOW,
            .bg = AMP_BG_YELLOW
        },
        .code   = { .fg = 33, .bg = 43 },
        .bitset = { .bright = true }
    },
    [AMP_BLUE] = {
        .index  = AMP_BLUE,     .rgb    = { .r  = 0,    .g  = 0,    .b  = 255 },
        .style  = {
            .fg = AMP_FG_BLUE,
            .bg = AMP_BG_BLUE
        },
        .code   = { .fg = 34, .bg = 44 },
        .bitset = { .bright = true }
    },
    [AMP_FUCHSIA] = {
        .index  = AMP_FUCHSIA,  .rgb    = { .r  = 255,  .g  = 0,    .b  = 255 },
        .style  = {
            .fg = AMP_FG_FUCHSIA,
            .bg = AMP_BG_FUCHSIA
        },
        .code   = { .fg = 35, .bg = 45 },
        .bitset = { .bright = true }
    },
    [AMP_AQUA] = {
        .index  = AMP_AQUA,     .rgb    = { .r  = 0,    .g  = 255,  .b  = 255 },
        .style  = {
            .fg = AMP_FG_AQUA,
            .bg = AMP_BG_AQUA
        },
        .code   = { .fg = 36, .bg = 46 },
        .bitset = { .bright = true }
    },
    [AMP_WHITE] = {
        .index  = AMP_WHITE,    .rgb    = { .r  = 255,  .g  = 255,  .b  = 255 },
        .style  = {
            .fg = AMP_FG_WHITE,
            .bg = AMP_BG_WHITE
        },
        .code   = { .fg = 37, .bg = 47 },
        .bitset = { .bright = true }
    },
    ////////////////////////////////////////////////////////////////////////////
    [AMP_MAX_COLOR] = {}
};

static const struct amp_color_combo_type amp_color_combo_table[] = {
    { { AMP_DARK } },
    { { AMP_DARK, AMP_MAROON } },
    { { AMP_DARK, AMP_MAROON } },
    { { AMP_DARK, AMP_RED } },
    { { AMP_MAROON } },
    { { AMP_MAROON, AMP_RED } },
    { { AMP_RED } },
    { { AMP_RED } },
    { { AMP_DARK, AMP_PURPLE, AMP_LIME } },
    { { AMP_DARK, AMP_MAROON, AMP_GREEN } },
    { { AMP_DARK, AMP_GREEN, AMP_RED } },
    { { AMP_DARK, AMP_OLIVE, AMP_RED } },
    { { AMP_DARK, AMP_MAROON, AMP_RED, AMP_YELLOW } },
    { { AMP_MAROON, AMP_OLIVE, AMP_RED } },
    { { AMP_RED } },
    { { AMP_RED } },
    { { AMP_DARK, AMP_GREEN } },
    { { AMP_DARK, AMP_MAROON, AMP_LIME } },
    { { AMP_DARK, AMP_OLIVE } },
    { { AMP_GREEN, AMP_RED } },
    { { AMP_MAROON, AMP_OLIVE } },
    { { AMP_OLIVE, AMP_RED } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW } },
    { { AMP_DARK, AMP_LIME } },
    { { AMP_DARK, AMP_OLIVE, AMP_LIME } },
    { { AMP_MAROON, AMP_LIME } },
    { { AMP_DARK, AMP_YELLOW } },
    { { AMP_MAROON, AMP_RED, AMP_LIME, AMP_YELLOW } },
    { { AMP_MAROON, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_RED, AMP_YELLOW } },
    { { AMP_RED, AMP_YELLOW } },
    { { AMP_GREEN } },
    { { AMP_DARK, AMP_GREEN, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_OLIVE } },
    { { AMP_GREEN, AMP_RED, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE } },
    { { AMP_GREEN, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_GREEN, AMP_LIME } },
    { { AMP_GREEN, AMP_OLIVE, AMP_LIME } },
    { { AMP_OLIVE, AMP_LIME } },
    { { AMP_GREEN, AMP_YELLOW } },
    { { AMP_MAROON, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_YELLOW } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_GREEN, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_YELLOW } },
    { { AMP_YELLOW } },
    { { AMP_LIME } },
    { { AMP_LIME } },
    { { AMP_LIME } },
    { { AMP_LIME, AMP_YELLOW } },
    { { AMP_LIME, AMP_YELLOW } },
    { { AMP_LIME, AMP_YELLOW, AMP_WHITE } },
    { { AMP_YELLOW } },
    { { AMP_YELLOW } },
    { { AMP_DARK, AMP_NAVY } },
    { { AMP_DARK, AMP_MAROON, AMP_NAVY } },
    { { AMP_DARK, AMP_NAVY, AMP_RED } },
    { { AMP_DARK, AMP_PURPLE, AMP_RED } },
    { { AMP_DARK, AMP_MAROON, AMP_RED, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_PURPLE, AMP_RED } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_GREEN, AMP_NAVY } },
    { { AMP_DARK, AMP_MAROON, AMP_TEAL } },
    { { AMP_DARK, AMP_TEAL, AMP_RED } },
    { { AMP_DARK, AMP_MAROON, AMP_OLIVE, AMP_PURPLE } },
    { { AMP_MAROON, AMP_OLIVE, AMP_PURPLE } },
    { { AMP_MAROON, AMP_CHARCOAL, AMP_RED } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_NAVY, AMP_LIME } },
    { { AMP_DARK, AMP_PURPLE, AMP_LIME } },
    { { AMP_DARK, AMP_MAROON, AMP_GREEN, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_MAROON, AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_OLIVE, AMP_SILVER, AMP_RED } },
    { { AMP_PURPLE, AMP_RED, AMP_YELLOW } },
    { { AMP_PURPLE, AMP_RED, AMP_YELLOW } },
    { { AMP_DARK, AMP_TEAL, AMP_LIME } },
    { { AMP_DARK, AMP_GREEN, AMP_OLIVE, AMP_TEAL } },
    { { AMP_DARK, AMP_GREEN, AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_GREEN, AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_MAROON, AMP_SILVER, AMP_YELLOW } },
    { { AMP_TEAL, AMP_RED, AMP_YELLOW } },
    { { AMP_MAROON, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_MAROON, AMP_RED, AMP_YELLOW } },
    { { AMP_DARK, AMP_GREEN, AMP_LIME, AMP_AQUA } },
    { { AMP_GREEN, AMP_OLIVE, AMP_TEAL } },
    { { AMP_GREEN, AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_GREEN, AMP_SILVER, AMP_YELLOW } },
    { { AMP_DARK, AMP_OLIVE, AMP_SILVER, AMP_YELLOW } },
    { { AMP_GREEN, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_RED, AMP_YELLOW } },
    { { AMP_GREEN, AMP_TEAL, AMP_LIME } },
    { { AMP_GREEN, AMP_CHARCOAL, AMP_LIME } },
    { { AMP_NAVY, AMP_LIME, AMP_YELLOW } },
    { { AMP_PURPLE, AMP_LIME, AMP_YELLOW } },
    { { AMP_MAROON, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_CHARCOAL, AMP_YELLOW } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_RED, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_GREEN, AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_TEAL, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_OLIVE, AMP_YELLOW, AMP_WHITE } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_LIME } },
    { { AMP_LIME } },
    { { AMP_LIME } },
    { { AMP_LIME, AMP_YELLOW } },
    { { AMP_LIME, AMP_YELLOW } },
    { { AMP_LIME, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_YELLOW } },
    { { AMP_DARK, AMP_NAVY } },
    { { AMP_DARK, AMP_MAROON, AMP_BLUE } },
    { { AMP_DARK, AMP_PURPLE } },
    { { AMP_NAVY, AMP_RED } },
    { { AMP_MAROON, AMP_PURPLE } },
    { { AMP_PURPLE, AMP_RED } },
    { { AMP_MAROON, AMP_RED, AMP_FUCHSIA } },
    { { AMP_OLIVE, AMP_RED, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_GREEN, AMP_BLUE } },
    { { AMP_DARK, AMP_OLIVE, AMP_BLUE } },
    { { AMP_DARK, AMP_MAROON, AMP_NAVY, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_MAROON, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_GREEN, AMP_RED, AMP_FUCHSIA } },
    { { AMP_OLIVE, AMP_RED, AMP_FUCHSIA } },
    { { AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_TEAL } },
    { { AMP_DARK, AMP_GREEN, AMP_NAVY, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_OLIVE, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_CHARCOAL } },
    { { AMP_CHARCOAL, AMP_RED } },
    { { AMP_MAROON, AMP_RED, AMP_WHITE } },
    { { AMP_RED, AMP_YELLOW, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_LIME } },
    { { AMP_DARK, AMP_GREEN, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_OLIVE, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_OLIVE, AMP_SILVER } },
    { { AMP_GREEN, AMP_SILVER, AMP_RED } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_GREEN, AMP_TEAL } },
    { { AMP_GREEN, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_GREEN, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_SILVER, AMP_LIME } },
    { { AMP_OLIVE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_SILVER, AMP_YELLOW } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_RED, AMP_YELLOW } },
    { { AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_TEAL, AMP_LIME } },
    { { AMP_MAROON, AMP_LIME, AMP_AQUA } },
    { { AMP_CHARCOAL, AMP_LIME } },
    { { AMP_MAROON, AMP_LIME, AMP_WHITE } },
    { { AMP_GREEN, AMP_SILVER, AMP_YELLOW } },
    { { AMP_CHARCOAL, AMP_YELLOW } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_RED, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_LIME, AMP_AQUA } },
    { { AMP_OLIVE, AMP_LIME, AMP_AQUA } },
    { { AMP_GREEN, AMP_LIME, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_LIME, AMP_YELLOW } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_OLIVE, AMP_YELLOW, AMP_WHITE } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_LIME, AMP_YELLOW, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME, AMP_YELLOW } },
    { { AMP_LIME, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_YELLOW, AMP_WHITE } },
    { { AMP_DARK, AMP_BLUE } },
    { { AMP_DARK, AMP_PURPLE, AMP_BLUE } },
    { { AMP_MAROON, AMP_BLUE } },
    { { AMP_DARK, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_RED, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_RED, AMP_FUCHSIA } },
    { { AMP_RED, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_TEAL, AMP_BLUE } },
    { { AMP_DARK, AMP_NAVY, AMP_PURPLE, AMP_TEAL } },
    { { AMP_DARK, AMP_NAVY, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_NAVY, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_MAROON, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_TEAL, AMP_RED, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_RED, AMP_FUCHSIA } },
    { { AMP_GREEN, AMP_BLUE } },
    { { AMP_DARK, AMP_NAVY, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_PURPLE, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_PURPLE, AMP_SILVER } },
    { { AMP_NAVY, AMP_SILVER, AMP_RED } },
    { { AMP_NAVY, AMP_RED, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_RED, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_AQUA } },
    { { AMP_GREEN, AMP_NAVY, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_TEAL, AMP_SILVER } },
    { { AMP_DARK, AMP_SILVER } },
    { { AMP_TEAL, AMP_SILVER, AMP_RED } },
    { { AMP_MAROON, AMP_SILVER } },
    { { AMP_SILVER, AMP_RED } },
    { { AMP_RED, AMP_WHITE } },
    { { AMP_GREEN, AMP_LIME, AMP_BLUE, AMP_AQUA } },
    { { AMP_NAVY, AMP_TEAL, AMP_SILVER, AMP_LIME } },
    { { AMP_NAVY, AMP_SILVER, AMP_LIME } },
    { { AMP_PURPLE, AMP_SILVER, AMP_LIME } },
    { { AMP_NAVY, AMP_SILVER, AMP_YELLOW } },
    { { AMP_PURPLE, AMP_SILVER, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_YELLOW } },
    { { AMP_GREEN, AMP_AQUA } },
    { { AMP_PURPLE, AMP_LIME, AMP_AQUA } },
    { { AMP_OLIVE, AMP_AQUA } },
    { { AMP_GREEN, AMP_SILVER } },
    { { AMP_TEAL, AMP_SILVER, AMP_YELLOW } },
    { { AMP_OLIVE, AMP_SILVER } },
    { { AMP_PURPLE, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_RED, AMP_YELLOW, AMP_WHITE } },
    { { AMP_TEAL, AMP_LIME, AMP_AQUA } },
    { { AMP_GREEN, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_OLIVE, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME } },
    { { AMP_OLIVE, AMP_SILVER, AMP_LIME, AMP_WHITE } },
    { { AMP_TEAL, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_YELLOW } },
    { { AMP_MAROON, AMP_YELLOW, AMP_WHITE } },
    { { AMP_LIME, AMP_AQUA } },
    { { AMP_LIME, AMP_AQUA } },
    { { AMP_LIME, AMP_AQUA } },
    { { AMP_LIME, AMP_WHITE } },
    { { AMP_LIME, AMP_WHITE } },
    { { AMP_SILVER, AMP_LIME, AMP_YELLOW, AMP_WHITE } },
    { { AMP_GREEN, AMP_YELLOW, AMP_WHITE } },
    { { AMP_YELLOW, AMP_WHITE } },
    { { AMP_NAVY } },
    { { AMP_DARK, AMP_NAVY, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_PURPLE } },
    { { AMP_NAVY, AMP_RED, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE } },
    { { AMP_NAVY, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_NAVY, AMP_BLUE, AMP_AQUA } },
    { { AMP_NAVY, AMP_PURPLE, AMP_TEAL } },
    { { AMP_NAVY, AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_DARK, AMP_NAVY, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_DARK, AMP_PURPLE, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_TEAL } },
    { { AMP_NAVY, AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_NAVY, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_SILVER, AMP_BLUE } },
    { { AMP_PURPLE, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_RED, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_LIME, AMP_BLUE, AMP_AQUA } },
    { { AMP_DARK, AMP_NAVY, AMP_SILVER, AMP_AQUA } },
    { { AMP_GREEN, AMP_SILVER, AMP_BLUE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_BLUE } },
    { { AMP_GREEN, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_OLIVE, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_WHITE } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_TEAL } },
    { { AMP_DARK, AMP_TEAL, AMP_SILVER, AMP_AQUA } },
    { { AMP_TEAL, AMP_CHARCOAL } },
    { { AMP_MAROON, AMP_SILVER, AMP_AQUA } },
    { { AMP_CHARCOAL } },
    { { AMP_TEAL, AMP_SILVER, AMP_RED, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_RED, AMP_WHITE } },
    { { AMP_SILVER, AMP_RED, AMP_WHITE } },
    { { AMP_NAVY, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_NAVY, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_GREEN, AMP_SILVER, AMP_AQUA } },
    { { AMP_OLIVE, AMP_SILVER, AMP_AQUA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_LIME, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_YELLOW, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_LIME, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_LIME, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_LIME, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_WHITE } },
    { { AMP_PURPLE, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA } },
    { { AMP_SILVER, AMP_LIME, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_LIME, AMP_WHITE } },
    { { AMP_TEAL, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_YELLOW, AMP_WHITE } },
    { { AMP_NAVY, AMP_BLUE } },
    { { AMP_NAVY, AMP_PURPLE, AMP_BLUE } },
    { { AMP_PURPLE, AMP_BLUE } },
    { { AMP_NAVY, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_SILVER, AMP_RED, AMP_FUCHSIA } },
    { { AMP_RED, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_NAVY, AMP_TEAL, AMP_BLUE } },
    { { AMP_NAVY, AMP_CHARCOAL, AMP_BLUE } },
    { { AMP_GREEN, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_OLIVE, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_CHARCOAL, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_RED, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_BLUE } },
    { { AMP_NAVY, AMP_TEAL, AMP_SILVER, AMP_BLUE } },
    { { AMP_CHARCOAL, AMP_BLUE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE } },
    { { AMP_NAVY, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_CHARCOAL, AMP_FUCHSIA } },
    { { AMP_MAROON, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_RED, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA } },
    { { AMP_OLIVE, AMP_BLUE, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE } },
    { { AMP_NAVY, AMP_SILVER } },
    { { AMP_TEAL, AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER } },
    { { AMP_OLIVE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_GREEN, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_GREEN, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_NAVY, AMP_SILVER, AMP_AQUA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_AQUA } },
    { { AMP_OLIVE, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_RED, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_AQUA } },
    { { AMP_TEAL, AMP_CHARCOAL, AMP_AQUA } },
    { { AMP_CHARCOAL, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER } },
    { { AMP_TEAL, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_YELLOW, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_YELLOW, AMP_WHITE } },
    { { AMP_LIME, AMP_AQUA, AMP_WHITE } },
    { { AMP_LIME, AMP_AQUA, AMP_WHITE } },
    { { AMP_LIME, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_LIME, AMP_AQUA, AMP_WHITE } },
    { { AMP_YELLOW, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_YELLOW, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_WHITE } },
    { { AMP_NAVY, AMP_PURPLE, AMP_BLUE } },
    { { AMP_BLUE } },
    { { AMP_NAVY, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_CHARCOAL, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_CHARCOAL, AMP_FUCHSIA } },
    { { AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_NAVY, AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_TEAL, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_BLUE, AMP_AQUA } },
    { { AMP_PURPLE, AMP_BLUE, AMP_AQUA } },
    { { AMP_NAVY, AMP_BLUE, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_MAROON, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_BLUE, AMP_AQUA } },
    { { AMP_NAVY, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_SILVER, AMP_BLUE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_TEAL, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_FUCHSIA } },
    { { AMP_OLIVE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_BLUE, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_BLUE, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_FUCHSIA, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_AQUA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_GREEN, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_YELLOW, AMP_AQUA, AMP_WHITE } },
    { { AMP_OLIVE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_BLUE } },
    { { AMP_BLUE } },
    { { AMP_TEAL, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_FUCHSIA } },
    { { AMP_FUCHSIA } },
    { { AMP_NAVY, AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_NAVY, AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_TEAL, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_BLUE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_FUCHSIA } },
    { { AMP_FUCHSIA } },
    { { AMP_PURPLE, AMP_BLUE, AMP_AQUA } },
    { { AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_BLUE, AMP_FUCHSIA, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_SILVER, AMP_BLUE, AMP_FUCHSIA } },
    { { AMP_BLUE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_BLUE, AMP_AQUA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_BLUE, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_SILVER, AMP_BLUE, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_BLUE, AMP_AQUA } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_BLUE, AMP_AQUA } },
    { { AMP_SILVER, AMP_BLUE, AMP_AQUA } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_TEAL, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_AQUA, AMP_WHITE } },
    { { AMP_BLUE, AMP_AQUA, AMP_WHITE } },
    { { AMP_BLUE, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_BLUE, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_BLUE, AMP_WHITE } },
    { { AMP_FUCHSIA, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_FUCHSIA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_NAVY, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_FUCHSIA, AMP_AQUA, AMP_WHITE } },
    { { AMP_PURPLE, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_AQUA } },
    { { AMP_AQUA } },
    { { AMP_AQUA } },
    { { AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_AQUA, AMP_WHITE } },
    { { AMP_SILVER, AMP_CHARCOAL, AMP_AQUA, AMP_WHITE } },
    { { AMP_TEAL, AMP_SILVER, AMP_RED, AMP_AQUA, AMP_WHITE } },
    { { AMP_WHITE } }
};

static const char *amp_number_table[] = {
      "0",   "1",   "2",   "3",   "4",   "5",   "6",   "7",   "8",   "9",  "10",
     "11",  "12",  "13",  "14",  "15",  "16",  "17",  "18",  "19",  "20",  "21",
     "22",  "23",  "24",  "25",  "26",  "27",  "28",  "29",  "30",  "31",  "32",
     "33",  "34",  "35",  "36",  "37",  "38",  "39",  "40",  "41",  "42",  "43",
     "44",  "45",  "46",  "47",  "48",  "49",  "50",  "51",  "52",  "53",  "54",
     "55",  "56",  "57",  "58",  "59",  "60",  "61",  "62",  "63",  "64",  "65",
     "66",  "67",  "68",  "69",  "70",  "71",  "72",  "73",  "74",  "75",  "76",
     "77",  "78",  "79",  "80",  "81",  "82",  "83",  "84",  "85",  "86",  "87",
     "88",  "89",  "90",  "91",  "92",  "93",  "94",  "95",  "96",  "97",  "98",
     "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109",
    "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120",
    "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131",
    "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142",
    "143", "144", "145", "146", "147", "148", "149", "150", "151", "152", "153",
    "154", "155", "156", "157", "158", "159", "160", "161", "162", "163", "164",
    "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175",
    "176", "177", "178", "179", "180", "181", "182", "183", "184", "185", "186",
    "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197",
    "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208",
    "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219",
    "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230",
    "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241",
    "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252",
    "253", "254", "255"
};

static constexpr AMP_STYLE amp_fg_color_styles = (
    AMP_FG_NONE         | AMP_FG_DARK       | AMP_FG_MAROON     |
    AMP_FG_GREEN        | AMP_FG_OLIVE      | AMP_FG_NAVY       |
    AMP_FG_PURPLE       | AMP_FG_TEAL       | AMP_FG_SILVER     |
    AMP_FG_CHARCOAL     | AMP_FG_RED        | AMP_FG_LIME       |
    AMP_FG_YELLOW       | AMP_FG_BLUE       | AMP_FG_FUCHSIA    |
    AMP_FG_AQUA         | AMP_FG_WHITE
);

static constexpr AMP_STYLE amp_bg_color_styles = (
    AMP_BG_NONE         | AMP_BG_DARK       | AMP_BG_MAROON     |
    AMP_BG_GREEN        | AMP_BG_OLIVE      | AMP_BG_NAVY       |
    AMP_BG_PURPLE       | AMP_BG_TEAL       | AMP_BG_SILVER     |
    AMP_BG_CHARCOAL     | AMP_BG_RED        | AMP_BG_LIME       |
    AMP_BG_YELLOW       | AMP_BG_BLUE       | AMP_BG_FUCHSIA    |
    AMP_BG_AQUA         | AMP_BG_WHITE
);


static inline size_t amp_calc_size(uint32_t w, uint32_t h) {
    return AMP_CELL_SIZE * w * h;
}

static inline size_t amp_init(
    struct amp_type *amp, uint32_t w, uint32_t h, void *data, size_t data_size
) {
    if (data == nullptr) {
        data = (char *) amp->buffer;
        data_size = sizeof(amp->buffer);
    }

    const size_t bytes_required = amp_calc_size(w, h);
    const size_t cell_count = (
        (data_size < bytes_required ? data_size : bytes_required) /
        AMP_CELL_SIZE
    );
    const size_t glyph_size = cell_count * AMP_CELL_GLYPH_SIZE;
    const size_t mode_size = cell_count * AMP_CELL_MODE_SIZE;

    amp->canvas.data = data;
    amp->canvas.size = data_size;

    amp->canvas.glyph.data = (uint8_t *) data;
    amp->canvas.glyph.size = glyph_size;

    amp->canvas.mode.data = (uint8_t *) data + amp->canvas.glyph.size;
    amp->canvas.mode.size = mode_size;

    amp->width = w;
    amp->height = h;

    amp_clear(amp);

    return bytes_required;
}

static inline void amp_clear(struct amp_type *amp) {
    if (!amp) {
        return;
    }

    memset(amp->canvas.glyph.data, 0, amp->canvas.glyph.size);
    memset(amp->canvas.mode.data, 0, amp->canvas.mode.size);
}

static inline uint32_t amp_get_width(const struct amp_type *amp) {
    return amp->width;
}

static inline uint32_t amp_get_height(const struct amp_type *amp) {
    return amp->height;
}

static inline AMP_PALETTE amp_get_palette(const struct amp_type *amp) {
    return amp->palette;
}

static inline void amp_set_palette(struct amp_type *amp, AMP_PALETTE palette) {
    amp->palette = palette;
}

static inline ssize_t amp_get_cell_index(
    const struct amp_type *amp, long x, long y
) {
    if (x < 0 || y < 0 || x >= amp->width || y >= amp->height) {
        return -1;
    }

    return (y * amp->width + x);
}

static inline int amp_utf8_code_point_size(const char *str, size_t n) {
    uint8_t *s = (uint8_t *) str;

    if (n > 0) {
        uint8_t c = *s;

        if (c < 0x80) {
            return (c != 0 ? 1 : 0);
        }

        if (c >= 0xc2) {
            if (c < 0xe0) {
                if (n >= 2 && (s[1] ^ 0x80) < 0x40) {
                    return 2;
                }
            }
            else if (c < 0xf0) {
                if (n >= 3
                && (s[1] ^ 0x80) < 0x40
                && (s[2] ^ 0x80) < 0x40
                && (c >= 0xe1 || s[1] >= 0xa0)
                && (c != 0xed || s[1] < 0xa0)) {
                    return 3;
                }
            }
            else if (c < 0xf8) {
                if (n >= 4
                && (s[1] ^ 0x80) < 0x40
                && (s[2] ^ 0x80) < 0x40
                && (s[3] ^ 0x80) < 0x40
                && (c >= 0xf1 || s[1] >= 0x90)
                && (c < 0xf4 || (c == 0xf4 && s[1] < 0x90))) {
                    return 4;
                }
            }
        }
    }

    return -1; // invalid or incomplete multibyte character
}

static inline size_t amp_utf8_code_point_count(
    const char *utf8_str, size_t utf8_str_size
) {
    size_t code_point_count = 0;

    for (const char *s = utf8_str; *s;) {
        int cpsz = amp_utf8_code_point_size(
            s, amp_sub_size(utf8_str_size, (size_t) (s - utf8_str))
        );

        if (cpsz < 0) {
            break;
        }

        ++code_point_count;
        s += cpsz;
    }

    return code_point_count;
}

static inline const char *amp_get_glyph(
    const struct amp_type *amp, long x, long y
) {
    ssize_t cell_index = amp_get_cell_index(amp, x, y);

    if (cell_index < 0) {
        return nullptr;
    }

    if ((size_t) cell_index * AMP_CELL_GLYPH_SIZE >= amp->canvas.glyph.size) {
        return nullptr;
    }

    return (
        (const char *) amp->canvas.glyph.data +
        (size_t) cell_index * AMP_CELL_GLYPH_SIZE
    );
}

static inline ssize_t amp_copy_glyph(
    const struct amp_type *amp, long x, long y,
    uint8_t *glyph_dst, size_t glyph_dst_size
) {
    const char *glyph = amp_get_glyph(amp, x, y);

    if (!glyph) {
        if (glyph_dst_size) {
            *glyph_dst = 0;
        }

        return -1;
    }

    const size_t glyph_length = strlen(glyph);

    if (glyph_length >= glyph_dst_size || !glyph_length) {
        if (glyph_dst_size) {
            *glyph_dst = 0;
        }
    }
    else {
        memcpy(glyph_dst, glyph, glyph_length + 1);
    }

    return (
        // The number of characters that would have been written if
        // glyph_dst_size had been sufficiently large, not counting the
        // terminating null character.
        (ssize_t) glyph_length
    );
}

static inline const char *amp_put_glyph(
    struct amp_type *amp, long x, long y, const char *glyph
) {
    // If glyph contains multiple UTF8 code points, then use only the first one.

    ssize_t cell_index = amp_get_cell_index(amp, x, y);

    if (cell_index < 0) {
        return nullptr;
    }

    if ((size_t) cell_index * AMP_CELL_GLYPH_SIZE >= amp->canvas.glyph.size) {
        return nullptr;
    }

    uint8_t glyph_data[AMP_CELL_GLYPH_SIZE];
    uint8_t glyph_data_size = 0;

    for (; glyph_data_size < sizeof(glyph_data); ++glyph_data_size) {
        glyph_data[glyph_data_size] = (uint8_t) glyph[glyph_data_size];

        if (glyph_data[glyph_data_size] == 0) {
            break;
        }
    }

    int code_point_size = amp_utf8_code_point_size(
        (const char *) glyph_data, glyph_data_size
    );

    if (code_point_size < 0 || (size_t) code_point_size >= sizeof(glyph_data)) {
        return nullptr;
    }

    glyph_data[code_point_size] = 0;
    glyph_data_size = (uint8_t) code_point_size;

    char *dst = (char *) (
        amp->canvas.glyph.data + (size_t) cell_index * AMP_CELL_GLYPH_SIZE
    );

    memcpy(dst, glyph_data, glyph_data_size + 1);

    return dst;
}

static inline bool amp_set_mode(
    struct amp_type *amp, long x, long y, struct amp_mode_type mode
) {
    uint8_t *mode_data = amp_get_mode_data(amp, x, y);

    if (!mode_data) {
        return false;
    }

    return amp_mode_cell_serialize(mode, mode_data, AMP_CELL_MODE_SIZE);
}

static inline struct amp_mode_type amp_get_mode(
    const struct amp_type *amp, long x, long y
) {
    static const struct amp_mode_type broken_cell = {
        .bitset = { .broken = true }
    };

    uint8_t *mode_data = amp_get_mode_data(amp, x, y);

    if (!mode_data) {
        return broken_cell;
    }

    return amp_mode_cell_deserialize(mode_data, AMP_CELL_MODE_SIZE);
}

static inline uint8_t *amp_get_mode_data(
    const struct amp_type *amp, long x, long y
) {
    ssize_t cell_index = amp_get_cell_index(amp, x, y);

    if (cell_index < 0) {
        return nullptr;
    }

    if ((size_t) cell_index * AMP_CELL_MODE_SIZE >= amp->canvas.mode.size) {
        return nullptr;
    }

    return amp->canvas.mode.data + (size_t) cell_index * AMP_CELL_MODE_SIZE;
}

static inline AMP_STYLE amp_get_style(
    const struct amp_type *amp, long x, long y
) {
    AMP_STYLE style = AMP_STYLE_NONE;
    auto mode = amp_get_mode(amp, x, y);

    if (mode.bitset.broken) {
        return AMP_STYLE_NONE;
    }

    if (mode.bitset.bg) {
        auto const combo = amp_lookup_color_combo(mode.bg);

        for (size_t i=0; combo.colors[i] != AMP_COLOR_NONE; ++i) {
            style |= amp_lookup_color(combo.colors[i]).style.bg;
        }
    }

    if (mode.bitset.fg) {
        auto const combo = amp_lookup_color_combo(mode.fg);

        for (size_t i=0; combo.colors[i] != AMP_COLOR_NONE; ++i) {
            style |= amp_lookup_color(combo.colors[i]).style.fg;
        }
    }

    return (
        (mode.bitset.hidden         ? AMP_HIDDEN        : 0) |
        (mode.bitset.faint          ? AMP_FAINT         : 0) |
        (mode.bitset.italic         ? AMP_ITALIC        : 0) |
        (mode.bitset.underline      ? AMP_UNDERLINE     : 0) |
        (mode.bitset.blinking       ? AMP_BLINKING      : 0) |
        (mode.bitset.strikethrough  ? AMP_STRIKETHROUGH : 0) | style
    );
}

static inline bool amp_put_style(
    struct amp_type *amp, long x, long y, AMP_STYLE style
) {
    auto mode = amp_get_mode(amp, x, y);

    constexpr AMP_STYLE bg_colors = amp_bg_color_styles;
    constexpr AMP_STYLE fg_colors = amp_fg_color_styles;

    if (style & bg_colors) {
        if (style & AMP_BG_NONE) {
            mode.bitset.bg = false;
        }
        else {
            unsigned bg_r = 0;
            unsigned bg_g = 0;
            unsigned bg_b = 0;
            unsigned bg_colors = 0;

            mode.bitset.bg = true;

            for (AMP_COLOR i = AMP_COLOR_NONE + 1; i < AMP_MAX_COLOR; ++i) {
                auto row = amp_color_table[i];

                if (row.style.bg & style) {
                    bg_r += row.rgb.r;
                    bg_g += row.rgb.g;
                    bg_b += row.rgb.b;

                    ++bg_colors;
                }
            }

            bg_r /= bg_colors;
            bg_g /= bg_colors;
            bg_b /= bg_colors;

            mode.bg = amp_map_rgb(
                (uint8_t) bg_r, (uint8_t) bg_g, (uint8_t) bg_b
            );
        }
    }
    else mode.bitset.bg = false;

    if (style & fg_colors) {
        if (style & AMP_FG_NONE) {
            mode.bitset.fg = false;
        }
        else {
            unsigned fg_r = 0;
            unsigned fg_g = 0;
            unsigned fg_b = 0;
            unsigned fg_colors = 0;

            mode.bitset.fg = true;

            for (AMP_COLOR i = AMP_COLOR_NONE + 1; i < AMP_MAX_COLOR; ++i) {
                auto row = amp_color_table[i];

                if (row.style.fg & style) {
                    fg_r += row.rgb.r;
                    fg_g += row.rgb.g;
                    fg_b += row.rgb.b;

                    ++fg_colors;
                }
            }

            fg_r /= fg_colors;
            fg_g /= fg_colors;
            fg_b /= fg_colors;

            mode.fg = amp_map_rgb(
                (uint8_t) fg_r, (uint8_t) fg_g, (uint8_t) fg_b
            );
        }
    }
    else mode.bitset.fg = false;

    mode.bitset.hidden          = style & AMP_HIDDEN;
    mode.bitset.faint           = style & AMP_FAINT;
    mode.bitset.italic          = style & AMP_ITALIC;
    mode.bitset.underline       = style & AMP_UNDERLINE;
    mode.bitset.blinking        = style & AMP_BLINKING;
    mode.bitset.strikethrough   = style & AMP_STRIKETHROUGH;

    return amp_set_mode(amp, x, y, mode);
}

static inline bool amp_set_bg_color(
    struct amp_type *amp, long x, long y, struct amp_rgb_type bg_color
) {
    auto mode = amp_get_mode(amp, x, y);

    mode.bg = bg_color;
    mode.bitset.bg = true;

    return amp_set_mode(amp, x, y, mode);
}

static inline struct amp_rgb_type amp_get_bg_color(
    struct amp_type *amp, long x, long y
) {
    return amp_get_mode(amp, x, y).bg;
}

static inline bool amp_set_fg_color(
    struct amp_type *amp, long x, long y, struct amp_rgb_type fg_color
) {
    auto mode = amp_get_mode(amp, x, y);

    mode.fg = fg_color;
    mode.bitset.fg = true;

    return amp_set_mode(amp, x, y, mode);
}

static inline struct amp_rgb_type amp_get_fg_color(
    struct amp_type *amp, long x, long y
) {
    return amp_get_mode(amp, x, y).fg;
}

static inline void amp_print_glyph(
    struct amp_type *amp, long x, long y, AMP_STYLE style, const char *glyph_str
) {
    if (x < 0 || x >= amp->width || y < 0 || y >= amp->height
    ||  x > UINT32_MAX || y > UINT32_MAX) {
        return;
    }

    char glyph[AMP_CELL_GLYPH_SIZE] = {};
    size_t glyph_size = 0;

    for (const char *c = glyph_str; *c; ++c) {
        if (++glyph_size >= sizeof(glyph)) {
            break;
        }
    }

    int cpsz = amp_utf8_code_point_size(glyph_str, glyph_size);

    if (cpsz < 0 || cpsz >= (int) sizeof(glyph)) {
        return;
    }

    memcpy(glyph, glyph_str, (size_t) cpsz);

    if (cpsz == 1 && !isprint(glyph[0])) {
        glyph[0] = '?';
    }

    amp_put_glyph(amp, x, y, glyph);

    if ((style & amp_bg_color_styles) == false) {
        // If the new style does not include any background colors, then the
        // existing background color should remain in effect.

        auto old_mode = amp_get_mode(amp, x, y);

        amp_put_style(amp, x, y, style);

        auto new_mode = amp_get_mode(amp, x, y);

        new_mode.bg = old_mode.bg;
        new_mode.bitset.bg = old_mode.bitset.bg;

        amp_set_mode(amp, x, y, new_mode);
    }
    else {
        amp_put_style(amp, x, y, style);
    }
}

static inline void amp_print_line_clip(
    struct amp_type *amp, long x, long y, AMP_STYLE style, AMP_ALIGN align,
    const char *text, size_t text_size
) {
    if (y < 0 || y >= amp->height || y > UINT32_MAX) {
        return;
    }

    uint32_t text_width = (uint32_t) amp_utf8_code_point_count(text, text_size);

    if (align == AMP_ALIGN_RIGHT) {
        x = (x - text_width) + 1;
    }
    else if (align == AMP_ALIGN_CENTER) {
        x -= text_width / 2;
    }

    for (const char *s = text; *s;) {
        int cpsz = amp_utf8_code_point_size(
            s, amp_sub_size(text_size, (size_t) (s - text))
        );

        if (cpsz < 0) {
            break;
        }

        amp_print_glyph(amp, x, y, style, s);

        if (++x >= amp->width) {
            break;
        }

        s += cpsz;
    }
}

static inline void amp_print_rich_line_clip(
    struct amp_type *amp, long x, long y, AMP_STYLE *text_style,
    AMP_ALIGN align, const char *text, size_t text_size
) {
    if (y < 0 || y >= amp->height || y > UINT32_MAX) {
        return;
    }

    uint32_t text_width = (uint32_t) (
        amp_utf8_code_point_count(text, text_size) -
        amp_str_seg_style_sign_count(text, text_size)
    );

    if (align == AMP_ALIGN_RIGHT) {
        x = (x - text_width) + 1;
    }
    else if (align == AMP_ALIGN_CENTER) {
        x -= text_width / 2;
    }

    const char *s = text;
    size_t count = 0;

    while (*s && s < text + text_size) {
        const char *next = amp_str_seg_skip_style_sign(
            s, text_size - (size_t) (s - text)
        );

        if (next > text + text_size) {
            break;
        }

        if (s == next) { // no style sign detected
            next = amp_str_seg_skip_any_utf8_symbol(
                s, text_size - (size_t) (s - text)
            );

            if (s == next) {
                break;
            }

            {
                int cpsz = amp_utf8_code_point_size(
                    s, amp_sub_size(text_size, (size_t) (s - text))
                );

                if (cpsz < 0) {
                    break;
                }

                amp_print_glyph(amp, x++, y, *text_style, s);
            }

            s = next;
            continue;
        }
        else if (next - s == 1) { // double brace detected
            ++count; // double braces '{{' count for one style sign

            if (*next != '{') {
                abort();
            }

            amp_print_glyph(amp, x++, y, *text_style, "{");

            s = next + 1;
            continue;
        }

        auto const row = amp_lookup_inline_style(s+1);
        AMP_STYLE new_style = row.style;

        if (new_style) {
            if (new_style & AMP_HARD_RESET) {
                *text_style = 0; // Reset foreground, background and decoration.
                new_style &= ~AMP_HARD_RESET;
            }

            if (new_style & AMP_SOFT_RESET) {
                // Reset foreground and decoration. Leave background as is.
                *text_style &= amp_bg_color_styles;
                new_style &= ~AMP_SOFT_RESET;
            }

            if (new_style & amp_fg_color_styles) {
                // New style includes foreground color. Clear the old color.
                *text_style &= ~amp_fg_color_styles;
            }

            if (new_style & amp_bg_color_styles) {
                // New style includes background color. Clear the old color.
                *text_style &= ~amp_bg_color_styles;
            }

            *text_style |= new_style;
        }

        s = next;
    }
}

static inline void amp_print_line(
    struct amp_type *amp, long x, long y, AMP_STYLE style, AMP_ALIGN align,
    const char *text
) {
    amp_print_line_clip(amp, x, y, style, align, text, strlen(text));
}

static inline size_t amp_print_rich_text_clip(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE *text_style,
    uint32_t text_max_width, AMP_ALIGN text_alignment, const char *text_str,
    size_t text_str_size
) {
    if (!text_max_width) {
        text_max_width = UINT32_MAX;
    }

    size_t line_count = 0;
    const char *line = text_str;
    long y = 0;

    while (*line && line < text_str + text_str_size) {
        size_t line_size;
        const char *next_line = amp_str_seg_first_line_size(
            line, amp_sub_size(text_str_size, (size_t) (line - text_str)),
            &line_size
        );

        const size_t line_width = amp_rich_str_seg_width(line, line_size);

        if (line_width > text_max_width) {
            const char *clip_end = amp_rich_str_seg_skip_wrap(
                line, line_size, text_max_width
            );

            const size_t clip_size = (size_t) (clip_end - line);

            amp_print_rich_line_clip(
                amp, text_x, text_y + y, text_style, text_alignment,
                line, clip_size
            );

            ++y;
            ++line_count;

            if (clip_size < line_size) {
                const char *space_end = amp_str_seg_skip_spaces(
                    clip_end, amp_sub_size(line_size, clip_size)
                );

                const size_t space_size = (size_t) (space_end - clip_end);
                const size_t trail_size = amp_sub_size(
                    line_size, clip_size + space_size
                );

                if (trail_size) {
                    size_t extra_lines = amp_print_rich_text_clip(
                        amp, text_x, text_y + y, text_style, text_max_width,
                        text_alignment, space_end, trail_size
                    );

                    y += (long) extra_lines;
                    line_count += extra_lines;
                }
            }
        }
        else {
            amp_print_rich_line_clip(
                amp, text_x, text_y + y, text_style, text_alignment,
                line, line_size
            );

            ++y;
            ++line_count;
        }

        if (next_line <= line) {
            break;
        }

        line = next_line;
    }

    return line_count;
}

static inline size_t amp_print_text_clip(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE text_style,
    uint32_t text_max_width, AMP_ALIGN text_alignment, const char *text_str,
    size_t text_str_size
) {
    if (!text_max_width) {
        text_max_width = UINT32_MAX;
    }

    size_t line_count = 0;
    const char *line = text_str;
    long y = 0;

    while (*line && line < text_str + text_str_size) {
        size_t line_size;
        const char *next_line = amp_str_seg_first_line_size(
            line, amp_sub_size(text_str_size, (size_t) (line - text_str)),
            &line_size
        );

        const size_t line_width = amp_str_seg_width(line, line_size);

        if (line_width > text_max_width) {
            const char *clip_end = amp_str_seg_skip_wrap(
                line, line_size, text_max_width
            );

            const size_t clip_size = (size_t) (clip_end - line);

            amp_print_line_clip(
                amp, text_x, text_y + y, text_style, text_alignment,
                line, clip_size
            );

            ++y;
            ++line_count;

            if (clip_size < line_size) {
                const char *space_end = amp_str_seg_skip_spaces(
                    clip_end, amp_sub_size(line_size, clip_size)
                );

                const size_t space_size = (size_t) (space_end - clip_end);
                const size_t trail_size = amp_sub_size(
                    line_size, clip_size + space_size
                );

                if (trail_size) {
                    size_t extra_lines = amp_print_text_clip(
                        amp, text_x, text_y + y, text_style, text_max_width,
                        text_alignment, space_end, trail_size
                    );

                    y += (long) extra_lines;
                    line_count += extra_lines;
                }
            }
        }
        else {
            amp_print_line_clip(
                amp, text_x, text_y + y, text_style, text_alignment,
                line, line_size
            );

            ++y;
            ++line_count;
        }

        if (next_line <= line) {
            break;
        }

        line = next_line;
    }

    return line_count;
}

static inline size_t amp_print_text(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE text_style,
    uint32_t text_max_width, AMP_ALIGN text_alignment, const char *text_str
) {
    return amp_print_text_clip(
        amp, text_x, text_y, text_style, text_max_width, text_alignment,
        text_str, strlen(text_str)
    );
}

static inline ssize_t amp_snprint_linef(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE text_style,
    AMP_ALIGN text_alignment, char *buf, size_t buf_size, const char *fmt, ...
) {
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(buf, buf_size, fmt, args);
    va_end(args);

    if (ret < 0) {
        return -1;
    }

    if ((size_t) ret >= buf_size) {
        return (ssize_t) ret;
    }

    amp_print_line(amp, text_x, text_y, text_style, text_alignment, buf);

    return (ssize_t) ret;
}

static inline ssize_t amp_snprint_textf(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE text_style,
    uint32_t text_max_width, AMP_ALIGN text_alignment,
    char *buf, size_t buf_size, const char *fmt, ...
) {
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(buf, buf_size, fmt, args);
    va_end(args);

    if (ret < 0) {
        return -1;
    }

    if ((size_t) ret >= buf_size) {
        return (ssize_t) ret;
    }

    amp_print_text(
        amp, text_x, text_y, text_style, text_max_width, text_alignment, buf
    );

    return (ssize_t) ret;
}

static inline ssize_t amp_snprint_rich_textf(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE text_style,
    uint32_t text_max_width, AMP_ALIGN text_alignment,
    char *buf, size_t buf_size, const char *fmt, ...
) {
    va_list args;
    va_start(args, fmt);
    int ret = vsnprintf(buf, buf_size, fmt, args);
    va_end(args);

    if (ret < 0) {
        return -1;
    }

    if ((size_t) ret >= buf_size) {
        return (ssize_t) ret;
    }

    amp_print_rich_text(
        amp, text_x, text_y, text_style, text_max_width, text_alignment, buf
    );

    return (ssize_t) ret;
}

static inline size_t amp_print_rich_text(
    struct amp_type *amp, long text_x, long text_y, AMP_STYLE style,
    uint32_t text_max_width, AMP_ALIGN text_alignment, const char *text_str
) {
    return amp_print_rich_text_clip(
        amp, text_x, text_y, &style, text_max_width, text_alignment,
        text_str, strlen(text_str)
    );
}

static inline size_t amp_str_append(
    char *str_dst, size_t str_dst_size, const char *str_src
) {
    const size_t str_src_size = strlen(str_src);

    if (str_src_size >= str_dst_size) {
        // No space for the terminating zero.

        if (str_dst_size) {
            *str_dst = '\0';
        }
    }
    else {
        memcpy(str_dst, str_src, str_src_size + 1);
    }

    return (
        // The number of characters that would have been written if
        // str_dst_size had been sufficiently large, not counting the
        // terminating null character.
        str_src_size
    );
}

static inline struct amp_mode_code_type amp_mode_to_codes(
    struct amp_mode_type mode, AMP_PALETTE pal
) {
    const struct {
        uint8_t code;
        bool    enabled;
    } styles[] = {
        { 8, mode.bitset.hidden        },
        { 2, mode.bitset.faint         },
        { 3, mode.bitset.italic        },
        { 4, mode.bitset.underline     },
        { 5, mode.bitset.blinking      },
        { 9, mode.bitset.strikethrough }
    };

    struct amp_mode_code_type codes = {};

    for (size_t i=0; i<sizeof(styles)/sizeof(styles[0]); ++i) {
        auto const value = styles[i];

        if (!value.enabled) {
            continue;
        }

        codes.style.data[codes.style.size++] = value.code;
    }

    if (pal == AMP_PAL_24BIT) {
        if (mode.bitset.fg) {
            codes.color.fg.data[codes.color.fg.size++] = 38;
            codes.color.fg.data[codes.color.fg.size++] = 2;
            codes.color.fg.data[codes.color.fg.size++] = mode.fg.r;
            codes.color.fg.data[codes.color.fg.size++] = mode.fg.g;
            codes.color.fg.data[codes.color.fg.size++] = mode.fg.b;
        }

        if (mode.bitset.bg) {
            codes.color.bg.data[codes.color.bg.size++] = 48;
            codes.color.bg.data[codes.color.bg.size++] = 2;
            codes.color.bg.data[codes.color.bg.size++] = mode.bg.r;
            codes.color.bg.data[codes.color.bg.size++] = mode.bg.g;
            codes.color.bg.data[codes.color.bg.size++] = mode.bg.b;
        }
    }
    else {
        if (mode.bitset.bg) {
            struct amp_color_type bg_color_row = amp_find_color(mode.bg);

            if (bg_color_row.bitset.bright) {
                struct amp_rgb_type buf = mode.bg;
                mode.bg = mode.fg;
                mode.fg = buf;
                mode.bitset.bg = mode.bitset.fg;
                mode.bitset.fg = true;

                codes.style.data[codes.style.size++] = 7; // inverse video
            }
        }

        if (mode.bitset.fg) {
            auto fg_color_row = amp_find_color(mode.fg);

            if (fg_color_row.bitset.bright) {
                codes.style.data[codes.style.size++] = 1; // bold foreground
            }

            codes.color.fg.data[codes.color.fg.size++] = fg_color_row.code.fg;
        }

        if (mode.bitset.bg) {
            struct amp_color_type bg_color_row = amp_find_color(mode.bg);

            codes.color.bg.data[codes.color.bg.size++] = bg_color_row.code.bg;
        }
    }

    return codes;
}

static inline struct amp_mode_code_type amp_mode_code_update(
    struct amp_mode_code_type next_codes, struct amp_mode_code_type prev_codes
) {
    struct amp_mode_code_type codes = {};

    do {
        const uint8_t n_fg = next_codes.color.fg.size;
        const uint8_t n_bg = next_codes.color.bg.size;

        if (n_fg) {
            uint8_t *prev_fg_data = prev_codes.color.fg.data;
            uint8_t *next_fg_data = next_codes.color.fg.data;

            if (prev_codes.color.fg.size && n_fg != prev_codes.color.fg.size) {
                // Color palette has changed. Full reset is needed.
                break;
            }

            if (n_fg != prev_codes.color.fg.size
            || memcmp(next_fg_data, prev_fg_data, n_fg)) {
                memcpy(codes.color.fg.data, next_fg_data, n_fg);
                codes.color.fg.size = n_fg;
            }
        }
        else if (prev_codes.color.fg.size) {
            // Foreground color is no longer set. Full reset is needed.
            break;
        }

        if (n_bg) {
            uint8_t *prev_bg_data = prev_codes.color.bg.data;
            uint8_t *next_bg_data = next_codes.color.bg.data;

            if (prev_codes.color.bg.size && n_bg != prev_codes.color.bg.size) {
                // Color palette has changed. Full reset is needed.
                break;
            }

            if (n_bg != prev_codes.color.bg.size
            || memcmp(next_bg_data, prev_bg_data, n_bg)) {
                memcpy(codes.color.bg.data, next_bg_data, n_bg);
                codes.color.bg.size = n_bg;
            }
        }
        else if (prev_codes.color.bg.size) {
            // Background color is no longer set. Full reset is needed.
            break;
        }

        // First, let's see if any of the style codes has gone missing.
        bool missing = false;

        for (size_t i=0; i<prev_codes.style.size; ++i) {
            bool found = false;

            for (size_t j=0; j<next_codes.style.size; ++j) {
                if (next_codes.style.data[j] == prev_codes.style.data[i]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                missing = true;
                break;
            }
        }

        if (missing) {
            // A style code is no longer present. Full reset is needed.
            break;
        }

        for (size_t i=0; i<next_codes.style.size; ++i) {
            bool found = false;

            for (size_t j=0; j<prev_codes.style.size; ++j) {
                if (prev_codes.style.data[j] == next_codes.style.data[i]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                codes.style.data[codes.style.size++] = next_codes.style.data[i];
            }
        }

        return codes;
    } while (false);

    codes = next_codes;
    codes.bitset.reset = true;

    return codes;
}

static inline size_t amp_mode_codes_to_ans(
    struct amp_mode_code_type codes, char *ans_dst, size_t ans_dst_size
) {
    char ans[256];
    size_t ans_size = 0;

    if (codes.bitset.reset) {
        ans_size += (
            ans_size ? amp_str_append(
                ans + ans_size, amp_sub_size(sizeof(ans), ans_size), ";"
            ) : 0
        );

        ans_size += amp_str_append(
            ans + ans_size, amp_sub_size(sizeof(ans), ans_size),
            amp_number_table[0]
        );
    }

    for (size_t i=0; i<codes.style.size; ++i) {
        ans_size += (
            ans_size ? amp_str_append(
                ans + ans_size, amp_sub_size(sizeof(ans), ans_size), ";"
            ) : 0
        );

        ans_size += amp_str_append(
            ans + ans_size, amp_sub_size(sizeof(ans), ans_size),
            amp_number_table[codes.style.data[i]]
        );
    }

    for (size_t i=0; i<codes.color.fg.size; ++i) {
        ans_size += (
            ans_size ? amp_str_append(
                ans + ans_size, amp_sub_size(sizeof(ans), ans_size), ";"
            ) : 0
        );

        ans_size += amp_str_append(
            ans + ans_size, amp_sub_size(sizeof(ans), ans_size),
            amp_number_table[codes.color.fg.data[i]]
        );
    }

    for (size_t i=0; i<codes.color.bg.size; ++i) {
        ans_size += (
            ans_size ? amp_str_append(
                ans + ans_size, amp_sub_size(sizeof(ans), ans_size), ";"
            ) : 0
        );

        ans_size += amp_str_append(
            ans + ans_size, amp_sub_size(sizeof(ans), ans_size),
            amp_number_table[codes.color.bg.data[i]]
        );
    }

    size_t written = 0;

    if (ans_size) {
        written += amp_str_append(
            ans_dst + written, amp_sub_size(ans_dst_size, written), AMP_ESC "["
        );

        written += amp_str_append(
            ans_dst + written, amp_sub_size(ans_dst_size, written), ans
        );

        written += amp_str_append(
            ans_dst + written, amp_sub_size(ans_dst_size, written), "m"
        );
    }

    if (written >= ans_dst_size || !written) {
        if (ans_dst_size) {
            *ans_dst = '\0';
        }
    }

    return written;
}

static inline ssize_t amp_stdout(const char *str_src, size_t str_src_size) {
    size_t n = 0;

    for (; n < str_src_size;) {
        ssize_t written = write(STDOUT_FILENO, str_src + n, str_src_size - n);

        if (written <= 0) {
            break;
        }

        n += (size_t) written;
    }

    return n == str_src_size ? (ssize_t) n : -1;
}

static inline ssize_t amp_clip_to_ans(
    const struct amp_type *amp, long x, long y, uint32_t width,
    char *ans_dst, size_t ans_dst_size
) {
    if ((ans_dst >= (char *) amp->canvas.glyph.data
      && ans_dst <  (char *) amp->canvas.glyph.data + amp->canvas.glyph.size)
    ||  (ans_dst >= (char *) amp->canvas.mode.data
      && ans_dst <  (char *) amp->canvas.mode.data + amp->canvas.mode.size)) {
        abort(); // Overwriting its own memory is a fatal error.
    }

    const bool ans_to_stdout = (
        ans_dst == (char *) amp->buffer + sizeof(amp->buffer)
    );

    const uint32_t amp_width = amp->width;
    const long end_x = (
        width ? (x + width > amp_width ? amp_width : x + width) : amp_width
    );

    char glyph_data[AMP_CELL_GLYPH_SIZE];
    char mode_ans[256];
    struct amp_mode_code_type prev_mode_codes = {};
    size_t ans_size = 0;

    for (; x < end_x; ++x) {
        auto next_mode_codes = amp_mode_to_codes(
            amp_get_mode(amp, x, y), amp->palette
        );

        auto add_mode_codes = amp_mode_code_update(
            next_mode_codes, prev_mode_codes
        );

        prev_mode_codes = next_mode_codes;

        const size_t mode_ans_size = amp_mode_codes_to_ans(
            add_mode_codes, mode_ans, sizeof(mode_ans)
        );

        if (mode_ans_size >= sizeof(mode_ans)) {
            abort(); // The mode_ans buffer should fit any mode.
        }
        else if (mode_ans_size) {
            if (ans_to_stdout) {
                if (amp_stdout(mode_ans, mode_ans_size) < 0) {
                    return -1;
                }

                ans_size += mode_ans_size;
            }
            else {
                ans_size += amp_str_append(
                    ans_dst + ans_size, amp_sub_size(ans_dst_size, ans_size),
                    mode_ans
                );
            }
        }

        const ssize_t glyph_size = amp_copy_glyph(
            amp, x, y, (uint8_t *) glyph_data, sizeof(glyph_data)
        );

        if (glyph_size <= 0
        ||  glyph_size >= (ssize_t) sizeof(glyph_data)
        || (glyph_size == 1 && !isprint(*glyph_data))) {
            const char *space = " ";
            const size_t space_size = strlen(space);

            if (ans_to_stdout) {
                if (amp_stdout(space, space_size) < 0) {
                    return -1;
                }

                ans_size += space_size;
            }
            else {
                ans_size += amp_str_append(
                    ans_dst + ans_size, amp_sub_size(ans_dst_size, ans_size),
                    space
                );
            }

            continue;
        }

        if (ans_to_stdout) {
            if (amp_stdout(glyph_data, (size_t) glyph_size) < 0) {
                return -1;
            }

            ans_size += (size_t) glyph_size;
        }
        else {
            ans_size += amp_str_append(
                ans_dst + ans_size, amp_sub_size(ans_dst_size, ans_size),
                glyph_data
            );
        }
    }

    if (prev_mode_codes.style.size
    ||  prev_mode_codes.color.bg.size
    ||  prev_mode_codes.color.fg.size) {
        const char *esc_reset = AMP_ESC "[0m";
        const size_t esc_reset_size = strlen(esc_reset);

        if (ans_to_stdout) {
            if (amp_stdout(esc_reset, strlen(esc_reset)) < 0) {
                return -1;
            }

            ans_size += esc_reset_size;
        }
        else {
            ans_size += amp_str_append(
                ans_dst + ans_size, amp_sub_size(ans_dst_size, ans_size),
                esc_reset
            );

            if (ans_size >= ans_dst_size || !ans_size) {
                if (ans_dst_size) {
                    *ans_dst = '\0';
                }
            }
        }
    }

    return (
        // The number of characters that would have been written if
        // ans_dst_size had been sufficiently large, not counting the
        // terminating null character.
        ans_size > SSIZE_MAX ? -1 : (ssize_t) ans_size
    );
}

static inline ssize_t amp_row_to_ans(
    const struct amp_type *amp, long y, char *ans_dst, size_t ans_dst_size
) {
    return (
        // The number of characters that would have been written if
        // ans_dst_size had been sufficiently large, not counting the
        // terminating null character. Returns -1 on error.
        amp_clip_to_ans(amp, 0, y, amp->width, ans_dst, ans_dst_size)
    );
}

static inline size_t amp_sub_size(size_t a, size_t b) {
    size_t result;
    return ckd_sub(&result, a, b) ? 0 : result;
}

static inline ssize_t amp_to_ans(
    const struct amp_type *amp, char *ans_dst, size_t ans_dst_size
) {
    if (ans_dst == nullptr) {
        ans_dst = (char *) amp->buffer + sizeof(amp->buffer);
        ans_dst_size = 0;
    }
    else {
        uint8_t *dst = (uint8_t *) ans_dst;

        if ((dst >= amp->canvas.glyph.data
          && dst <  amp->canvas.glyph.data + amp->canvas.glyph.size)
        ||  (dst >= amp->canvas.mode.data
          && dst <  amp->canvas.mode.data + amp->canvas.mode.size)) {
            abort(); // Overwriting its own memory is a fatal error.
        }
    }

    const bool ans_to_stdout = (
        ans_dst == (char *) amp->buffer + sizeof(amp->buffer)
    );

    size_t ans_size = 0;

    for (uint32_t y = 0; y < amp->height; ++y) {
        ssize_t size = amp_row_to_ans(
            amp, y, ans_to_stdout ? ans_dst : ans_dst + ans_size,
            amp_sub_size(ans_dst_size, ans_size)
        );

        if (size < 0) {
            return -1;
        }

        ans_size += (size_t) size;

        if (y + 1 < amp->height) {
            const char *crlf = "\r\n";
            const size_t crlf_size = strlen(crlf);

            if (ans_to_stdout) {
                if (amp_stdout(crlf, crlf_size) < 0) {
                    return -1;
                }

                ans_size += crlf_size;
            }
            else {
                ans_size += amp_str_append(
                    ans_dst + ans_size, amp_sub_size(ans_dst_size, ans_size),
                    crlf
                );
            }
        }
    }

    if (!ans_to_stdout) {
        if (ans_size >= ans_dst_size || !ans_size) {
            if (ans_dst_size) {
                *ans_dst = '\0';
            }
        }
    }

    return ans_size > SSIZE_MAX ? -1 : (ssize_t) ans_size;
}

static inline struct amp_mode_type amp_mode_cell_deserialize(
    const uint8_t *data, size_t data_size
) {
    return (struct amp_mode_type) {
        .fg = {
            .r = data_size > 0 ? data[0] : 0,
            .g = data_size > 1 ? data[1] : 0,
            .b = data_size > 2 ? data[2] : 0
        },
        .bg = {
            .r = data_size > 3 ? data[3] : 0,
            .g = data_size > 4 ? data[4] : 0,
            .b = data_size > 5 ? data[5] : 0
        },
        .bitset = {
            .fg             = data_size > 6 ? data[6] & (1 << 0) : 0,
            .bg             = data_size > 6 ? data[6] & (1 << 1) : 0,
            .hidden         = data_size > 6 ? data[6] & (1 << 2) : 0,
            .faint          = data_size > 6 ? data[6] & (1 << 3) : 0,
            .italic         = data_size > 6 ? data[6] & (1 << 4) : 0,
            .underline      = data_size > 6 ? data[6] & (1 << 5) : 0,
            .blinking       = data_size > 6 ? data[6] & (1 << 6) : 0,
            .strikethrough  = data_size > 6 ? data[6] & (1 << 7) : 0,
            .broken         = data_size < AMP_CELL_MODE_SIZE
        }
    };
}

static inline bool amp_mode_cell_serialize(
    struct amp_mode_type cell, uint8_t *dst, size_t dst_size
) {
    if (dst_size < AMP_CELL_MODE_SIZE) {
        return false;
    }

    dst[0] = cell.fg.r;
    dst[1] = cell.fg.g;
    dst[2] = cell.fg.b;
    dst[3] = cell.bg.r;
    dst[4] = cell.bg.g;
    dst[5] = cell.bg.b;
    dst[6] = (
        (cell.bitset.fg             ? (1 << 0) : 0) |
        (cell.bitset.bg             ? (1 << 1) : 0) |
        (cell.bitset.hidden         ? (1 << 2) : 0) |
        (cell.bitset.faint          ? (1 << 3) : 0) |
        (cell.bitset.italic         ? (1 << 4) : 0) |
        (cell.bitset.underline      ? (1 << 5) : 0) |
        (cell.bitset.blinking       ? (1 << 6) : 0) |
        (cell.bitset.strikethrough  ? (1 << 7) : 0)
    );
    dst[7] = 0; // temporarily used when decoding style layers

    return true;
}

static inline struct amp_color_type amp_find_color(struct amp_rgb_type rgb) {
    long best_d = LONG_MAX;
    size_t best_row = 0;

    for (size_t i=0; i<AMP_MAX_COLOR; ++i) {
        auto const row = amp_color_table[i];

        if (row.index == AMP_COLOR_NONE) {
            continue;
        }

        long dr = rgb.r - row.rgb.r;
        long dg = rgb.g - row.rgb.g;
        long db = rgb.b - row.rgb.b;
        long d = 3 * dr * dr + 4 * dg * dg + 2 * db * db;

        if (d < best_d) {
            best_d = d;
            best_row = i;
        }
    }

    return amp_color_table[best_row];
}

static inline struct amp_color_type amp_lookup_color(AMP_COLOR index) {
    return (
        index < AMP_MAX_COLOR ? (
            amp_color_table[index]
        ) : amp_color_table[AMP_COLOR_NONE]
    );
}

static inline struct amp_inline_style_type amp_lookup_inline_style(
    const char *glyph
) {
    uint8_t glyph_data[AMP_CELL_GLYPH_SIZE];
    uint8_t glyph_data_size = 0;

    for (; glyph_data_size < sizeof(glyph_data); ++glyph_data_size) {
        glyph_data[glyph_data_size] = (uint8_t) glyph[glyph_data_size];

        if (glyph_data[glyph_data_size] == 0) {
            break;
        }
    }

    int code_point_size = amp_utf8_code_point_size(
        (const char *) glyph_data, glyph_data_size
    );

    if (code_point_size < 0 || (size_t) code_point_size >= sizeof(glyph_data)) {
        return amp_inline_style_table[0];
    }

    constexpr size_t table_size = (
        sizeof(amp_inline_style_table)/sizeof(amp_inline_style_table[0])
    );

    glyph_data[code_point_size] = 0;
    glyph_data_size = (uint8_t) code_point_size;

    if (glyph_data_size == 1) {
        char index = (char) glyph_data[0];

        if (index < 0 || (size_t) index >= table_size) {
            return amp_inline_style_table[0];
        }

        return amp_inline_style_table[(size_t) index];
    }

    return amp_inline_style_table[0];
}

static inline struct amp_color_combo_type amp_lookup_color_combo(
    struct amp_rgb_type rgb
) {
    constexpr size_t cube_w = 8;
    constexpr size_t cluster_w = cube_w;
    constexpr size_t cluster_h = cube_w;
    constexpr size_t table_size = (
        sizeof(amp_color_combo_table)/sizeof(amp_color_combo_table[0])
    );

    size_t cluster_x = rgb.r / (256 / cube_w);
    size_t cluster_y = rgb.g / (256 / cube_w);
    size_t cluster_z = rgb.b / (256 / cube_w);

    const size_t cluster_i = (
        (cluster_z * cluster_h + cluster_y) * cluster_w + cluster_x
    );

    return (
        cluster_i >= table_size ? (
            (struct amp_color_combo_type) {}
        ) : amp_color_combo_table[cluster_i]
    );
}

static inline struct amp_rgb_type amp_map_rgb(
    uint8_t r, uint8_t g, uint8_t b
) {
    return (struct amp_rgb_type) { .r = r, .g = g, .b = b };
}

static inline void amp_unmap_rgb(
    struct amp_rgb_type color, uint8_t * r, uint8_t * g, uint8_t * b
) {
    *r = color.r;
    *g = color.g;
    *b = color.b;
}

static inline const char *amp_str_seg_first_line_size(
    const char *str, size_t str_sz, size_t *line_size
) {
    const char *begin = str;
    const char *found = nullptr;
    char after_found;

    const char *s = str;

    while (*s && s < str + str_sz) {
        if (*s == '\n') {
            found = s;
            after_found = '\r';
            break;
        }
        else if (*s == '\r') {
            found = s;
            after_found = '\n';
            break;
        }

        ++s;
    }

    if (found) {
        if (*(s + 1) == after_found) {
            s += 2;
        }
        else {
            s += 1;
        }
    }

    if (line_size) {
        *line_size = found ? (size_t) (found - begin) : (size_t) (s - begin);
    }

    return s;
}

static inline const char *amp_str_seg_skip_any_utf8_symbol(
    const char *str, size_t str_sz
) {
    if (!str_sz) {
        return str;
    }

    int sz = amp_utf8_code_point_size(str, str_sz);

    if (sz == 0) {
        return str;
    }
    else if (sz < 0) {
        return str + 1;
    }

    return str + sz;
}

static inline const char *amp_str_seg_skip_str(
    const char *str_seg, size_t str_seg_sz, const char *str
) {
    const size_t str_sz = strlen(str);
    const size_t min_sz = str_seg_sz < str_sz ? str_seg_sz : str_sz;

    if (strncmp(str_seg, str, min_sz) == 0) {
        return str_seg + str_sz;
    }

    return str_seg;
}

static inline size_t amp_str_seg_style_sign_count(
    const char *str, size_t segment_sz
) {
    // return the number of zero-width rich text code symbols embedded in 'str'

    const char *s = str;
    size_t count = 0;

    while (*s && s < str + segment_sz) {
        const char *next = amp_str_seg_skip_style_sign(
            s, segment_sz - (size_t) (s - str)
        );

        if (next > str + segment_sz) {
            break;
        }

        if (s == next) { // no style sign detected
            next = amp_str_seg_skip_any_utf8_symbol(
                s, segment_sz - (size_t) (s - str)
            );

            if (s == next) {
                break;
            }

            s = next;
            continue;
        }
        else if (next - s == 1) { // double brace detected
            ++count; // double braces '{{' count for one style sign

            if (*next != '{') {
                abort();
            }

            s = next + 1;
            continue;
        }

        size_t diff = (size_t) (next - s);

        count += amp_utf8_code_point_count(s, diff);

        s = next;
    }

    return count;
}

static inline size_t amp_str_seg_width(const char *str, size_t str_sz) {
    const char *s = str;
    size_t width = 0;

    while (*s && s < str + str_sz) {
        size_t linesz;
        const char *next_line = amp_str_seg_first_line_size(
            s, str_sz - (size_t) (s - str), &linesz
        );

        size_t line_width = amp_utf8_code_point_count(s, linesz);

        width = width > line_width ? width : line_width;

        if (next_line <= s) {
            break;
        }

        s = next_line;
    }

    return width;
}

static inline size_t amp_rich_str_seg_width(const char *str, size_t str_sz) {
    const char *s = str;
    size_t width = 0;

    while (*s && s < str + str_sz) {
        size_t linesz;
        const char *next_line = amp_str_seg_first_line_size(
            s, str_sz - (size_t) (s - str), &linesz
        );

        size_t line_width = (
            amp_utf8_code_point_count(s, linesz) -
            amp_str_seg_style_sign_count(s, linesz)
        );

        width = width > line_width ? width : line_width;

        if (next_line <= s) {
            break;
        }

        s = next_line;
    }

    return width;
}

static inline const char *amp_str_seg_skip_spaces(
    const char *str, size_t str_sz
) {
    const char *s = str;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_any_utf8_symbol(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            break;
        }

        --next;

        if (*next != ' ') {
            return s;
        }

        s = next + 1;
    }

    return s;
}

static inline const char *amp_str_seg_skip_word(
    const char *str, size_t str_sz
) {
    const char *s = amp_str_seg_skip_spaces(str, str_sz);

    if (s != str) {
        return str;
    }

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_any_utf8_symbol(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            return s;
        }

        --next;

        if (*next == ' ') {
            return s;
        }

        s = next + 1;
    }

    return s;
}

static inline const char *amp_str_seg_skip_width(
    const char *str, size_t str_sz, size_t max_width
) {
    const char *s = str;
    size_t width = 0;

    while (*s && s < str + str_sz) {
        if (width++ >= max_width) {
            break;
        }

        const char *next = amp_str_seg_skip_any_utf8_symbol(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            break;
        }

        s = next;
    }

    return s;
}

static inline const char *amp_str_seg_skip_wrap(
    const char *str, size_t str_sz, size_t wrap_width
) {
    const char *s = str;
    size_t width = 0;
    size_t max_width = wrap_width;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_spaces(
            s, str_sz - (size_t) (s - str)
        );

        next = amp_str_seg_skip_word(next, str_sz - (size_t) (next - str));

        if (next == s) {
            break;
        }

        size_t diff = (size_t) (next - s);
        size_t add_width = amp_utf8_code_point_count(s, diff);
        size_t next_width = width + add_width;

        if (next_width > max_width) {
            if (!width) {
                return amp_str_seg_skip_width(str, str_sz, wrap_width);
            }

            break;
        }

        width = next_width;
        s = next;
    }

    return s;
}

static inline const char *amp_rich_str_seg_skip_wrap(
    const char *str, size_t str_sz, size_t wrap_width
) {
    const char *s = str;
    size_t width = 0;
    size_t max_width = wrap_width;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_style_and_spaces(
            s, str_sz - (size_t) (s - str)
        );

        next = amp_str_seg_skip_style_and_word(
            next, str_sz - (size_t) (next - str)
        );

        const char *after_trailing_style = amp_str_seg_skip_styles(
            next, str_sz - (size_t) (next - str)
        );

        if (str + str_sz == after_trailing_style) {
            next = after_trailing_style;
        }

        if (next == s) {
            break;
        }

        size_t diff = (size_t) (next - s);
        size_t add_width = amp_utf8_code_point_count(s, diff);
        size_t style_width = amp_str_seg_style_sign_count(s, diff);

        size_t next_width = width + add_width;
        size_t next_max_width = max_width + style_width;

        if (next_width > next_max_width) {
            if (!width) {
                return amp_str_seg_skip_width(str, str_sz, wrap_width);
            }

            break;
        }

        width = next_width;
        max_width = next_max_width;
        s = next;
    }

    return s;
}

static inline const char *amp_str_seg_skip_style_sign(
    const char *str, size_t str_sz
) {
    const char *s = str;
    bool style = false;

    while (*s && s < str + str_sz) {
        if (*s == '{' && !style) {
            style = true;
        }
        else if (style) {
            if (*s == '{') {
                return s;
            }

            const char *end = amp_str_seg_skip_any_utf8_symbol(
                s, str_sz - (size_t) (s - str)
            );

            return end > s ? end : str;
        }
        else break;

        ++s;
    }

    return str;
}

static inline const char *amp_str_seg_skip_style_and_spaces(
    const char *str, size_t str_sz
) {
    const char *s = str;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_style_and_utf8_symbol(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            return s;
        }

        --next;

        if (*next != ' ') {
            return s;
        }

        s = next + 1;
    }

    return s;
}

static inline const char *amp_str_seg_skip_style_and_word(
    const char *str, size_t str_sz
) {
    const char *s = amp_str_seg_skip_style_and_spaces(str, str_sz);

    if (s != str) {
        return str;
    }

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_style_and_utf8_symbol(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            return s;
        }

        --next;

        if (*next == ' ') {
            return s;
        }

        s = next + 1;
    }

    return s;
}

static inline const char *amp_str_seg_skip_styles(
    const char *str, size_t str_sz
) {
    const char *s = str;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_style_sign(
            s, str_sz - (size_t) (s - str)
        );

        if (next <= s + 1) {
            // If we fail to advance or if we advance only by 1, then we must
            // have reached the end of the style sequence.
            s = next;
            break;
        }

        s = next;
    }

    return s;
}

static inline const char *amp_str_seg_skip_style_and_utf8_symbol(
    const char *str, size_t str_sz
) {
    const char *s = str;

    while (*s && s < str + str_sz) {
        const char *next = amp_str_seg_skip_style_sign(
            s, str_sz - (size_t) (s - str)
        );

        if (next == s) {
            next = amp_str_seg_skip_any_utf8_symbol(
                next, str_sz - (size_t) (next - str)
            );

            if (next == s) {
                break;
            }
            else return next;
        }
        else if ((next - s) == 1) {
            const char *after_braces = amp_str_seg_skip_any_utf8_symbol(
                next, str_sz - (size_t) (next - str)
            );

            if (after_braces == next) {
                abort();
                break;
            }
            else if (*next != '{') {
                abort();
            }

            return after_braces;
        }

        s = next;
    }

    return str;
}

static inline struct amp_style_flag_type amp_lookup_style_flag(
    AMP_STYLE style
) {
    size_t index = stdc_first_trailing_one_ull(style);

    if (index >= sizeof(amp_style_flag_table)/sizeof(amp_style_flag_table[0])) {
        return amp_style_flag_table[0];
    }

    return amp_style_flag_table[index];
}

static inline ssize_t amp_encode_layer_cell(
    const struct amp_type *amp, long x, long y, AMP_STYLE style,
    char *buffer, size_t buffer_size
) {
    const bool to_stdout = (
        buffer == (char *) amp->buffer + sizeof(amp->buffer)
    );

    size_t written = 0;

    if (style == AMP_STYLE_NONE) {
        const char *glyph = amp_get_glyph(amp, x, y);

        if (!glyph || *glyph == '\0') {
            glyph = " ";
        }

        if (to_stdout) {
            if (amp_stdout(glyph, strlen(glyph)) < 0) {
                return -1;
            }

            written += strlen(glyph);
        }
        else {
            written += amp_str_append(
                buffer + written, amp_sub_size(buffer_size, written), glyph
            );
        }

        return written > SSIZE_MAX ? -1 : (ssize_t) written;
    }

    const char *glyph = " ";
    AMP_STYLE cell_style = amp_get_style(amp, x, y);
    AMP_STYLE matching_styles = cell_style & style;

    if (matching_styles) {
        auto const row = amp_lookup_style_flag(matching_styles);
        glyph = row.glyph;
    }

    if (!glyph || *glyph == '\0') {
        glyph = " ";
    }

    if (to_stdout) {
        if (amp_stdout(glyph, strlen(glyph)) < 0) {
            return -1;
        }

        written += strlen(glyph);
    }
    else {
        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written), glyph
        );
    }

    return written > SSIZE_MAX ? -1 : (ssize_t) written;
}

static inline ssize_t amp_encode_layer_row(
    const struct amp_type *amp, long y, AMP_STYLE style, char *buffer,
    size_t buffer_size
) {
    const bool to_stdout = (
        buffer == (char *) amp->buffer + sizeof(amp->buffer)
    );

    size_t written = 0;
    const char *left_border = "║";
    const char *right_border = "║\n";
    const size_t left_border_size = strlen(left_border);
    const size_t right_border_size = strlen(right_border);

    if (to_stdout) {
        if (amp_stdout(left_border, left_border_size) < 0) {
            return -1;
        }

        written += left_border_size;
    }
    else {
        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written), left_border
        );
    }

    for (long x=0; x<amp->width; ++x) {
        ssize_t ret = amp_encode_layer_cell(
            amp, x, y, style, to_stdout ? buffer : buffer + written,
            amp_sub_size(buffer_size, written)
        );

        if (ret < 0) {
            return -1;
        }

        written += (size_t) ret;
    }

    if (to_stdout) {
        if (amp_stdout(right_border, right_border_size) < 0) {
            return -1;
        }

        written += right_border_size;
    }
    else {
        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written), right_border
        );
    }

    return written > SSIZE_MAX ? -1 : (ssize_t) written;
}

static inline ssize_t amp_encode_layer(
    const struct amp_type *amp, AMP_SETTINGS settings, AMP_STYLE style,
    char *buffer, size_t buffer_size
) {
    const bool to_stdout = (
        buffer == (char *) amp->buffer + sizeof(amp->buffer)
    );

    size_t written = 0;

    if (style != AMP_STYLE_NONE) {
        const char *border = "═";
        const char *left_top_corner = "╠";
        const char *right_top_corner = "╣\n";
        const size_t left_top_corner_size = strlen(left_top_corner);
        const size_t right_top_corner_size = strlen(right_top_corner);
        const size_t border_size = strlen(border);

        if (to_stdout) {
            if (amp_stdout(left_top_corner, left_top_corner_size) < 0) {
                return -1;
            }

            written += left_top_corner_size;

            for (long x=0; x<amp->width; ++x) {
                if (amp_stdout(border, border_size) < 0) {
                    return -1;
                }

                written += border_size;
            }

            if (amp_stdout(right_top_corner, right_top_corner_size) < 0) {
                return -1;
            }

            written += right_top_corner_size;
        }
        else {
            written += amp_str_append(
                buffer + written, amp_sub_size(buffer_size, written),
                left_top_corner
            );

            for (long x=0; x<amp->width; ++x) {
                written += amp_str_append(
                    buffer + written, amp_sub_size(buffer_size, written), border
                );
            }

            written += amp_str_append(
                buffer + written, amp_sub_size(buffer_size, written),
                right_top_corner
            );
        }
    }

    long max_height = amp->height;

    if (style != AMP_STYLE_NONE && (settings & AMP_DEFLATE)) {
        for (long y=amp->height - 1; y >= 0; --y) {
            // Let's trim trailing empty rows for style layers.
            bool found = false;

            for (long x=0; x<amp->width; ++x) {
                AMP_STYLE cell_style = amp_get_style(amp, x, y);
                AMP_STYLE matching_styles = cell_style & style;

                if (matching_styles) {
                    found = true;
                    break;
                }
            }

            if (found) {
                max_height = y + 1;
                break;
            }
        }
    }

    for (long y=0; y<max_height; ++y) {
        ssize_t ret = amp_encode_layer_row(
            amp, y, style, to_stdout ? buffer : buffer + written,
            amp_sub_size(buffer_size, written)
        );

        if (ret < 0) {
            return -1;
        }

        written += (size_t) ret;
    }

    return written > SSIZE_MAX ? -1 : (ssize_t) written;
}

static inline AMP_STYLE amp_styles_to_layer(
    const struct amp_type *amp, AMP_STYLE whitelist
) {
    if (whitelist == AMP_STYLE_NONE) {
        return AMP_STYLE_NONE;
    }

    AMP_STYLE layer_styles = 0;
    AMP_STYLE blacklist = 0;

    for (long y = 0; y < amp->height; ++y) {
        for (long x = 0; x < amp->width; ++x) {
            AMP_STYLE style = amp_get_style(amp, x, y);
            AMP_STYLE match = style & whitelist & ~blacklist;

            if (!match) {
                continue;
            }

            layer_styles &= ~match;

            // Prefer the flag with the greatest value.
            size_t index = stdc_first_leading_one_ull(match);

            if (index) {
                constexpr AMP_STYLE most_significant_bit = 1ULL << 63;
                AMP_STYLE layer_style = most_significant_bit >> (index - 1);

                layer_styles |= layer_style;
                blacklist |= (match & ~layer_style);
            }
        }
    }

    return layer_styles;
}

static inline ssize_t amp_encode(
    const struct amp_type *amp, AMP_SETTINGS settings,
    char *buffer, size_t buffer_size
) {
    if (buffer == nullptr) {
        buffer = (char *) amp->buffer + sizeof(amp->buffer);
        buffer_size = 0;
    }
    else {
        uint8_t *buf = (uint8_t *) buffer;

        if ((buf >= amp->canvas.glyph.data
          && buf <  amp->canvas.glyph.data + amp->canvas.glyph.size)
        ||  (buf >= amp->canvas.mode.data
          && buf <  amp->canvas.mode.data + amp->canvas.mode.size)) {
            abort(); // Overwriting its own memory is a fatal error.
        }
    }

    const bool to_stdout = (
        buffer == (char *) amp->buffer + sizeof(amp->buffer)
    );

    const char *border = "═";
    const char *left_top_corner = "╔";
    const char *left_bottom_corner = "╚";
    const char *right_top_corner = "╗\n";
    const char *right_bottom_corner = "╝";
    const size_t left_top_corner_size = strlen(left_top_corner);
    const size_t right_top_corner_size = strlen(right_top_corner);
    const size_t left_bottom_corner_size = strlen(left_bottom_corner);
    const size_t right_bottom_corner_size = strlen(right_bottom_corner);
    const size_t border_size = strlen(border);

    size_t written = 0;

    if (to_stdout) {
        if (amp_stdout(left_top_corner, left_top_corner_size) < 0) {
            return -1;
        }

        written += left_top_corner_size;

        for (long x=0; x<amp->width; ++x) {
            if (amp_stdout(border, border_size) < 0) {
                return -1;
            }

            written += border_size;
        }

        if (amp_stdout(right_top_corner, right_top_corner_size) < 0) {
            return -1;
        }

        written += right_top_corner_size;
    }
    else {
        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written),
            left_top_corner
        );

        for (long x=0; x<amp->width; ++x) {
            written += amp_str_append(
                buffer + written, amp_sub_size(buffer_size, written), border
            );
        }

        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written),
            right_top_corner
        );
    }

    const AMP_STYLE style_groups[] = {
        AMP_STYLE_NONE,
        (settings & AMP_FLATTEN) ? AMP_STYLE_NONE : amp_fg_color_styles,
        (settings & AMP_FLATTEN) ? AMP_STYLE_NONE : amp_bg_color_styles,
        ~AMP_STYLE_NONE
    };

    AMP_STYLE style_pool = ~AMP_STYLE_NONE;

    for (size_t i=0; i<sizeof(style_groups)/sizeof(style_groups[0]); ++i) {
        AMP_STYLE layer_style;
        AMP_STYLE style_group = style_groups[i] & style_pool;

        do {
            layer_style = amp_styles_to_layer(amp, style_group);

            if (layer_style || i == 0) {
                ssize_t ret = amp_encode_layer(
                    amp, settings, layer_style,
                    to_stdout ? buffer : buffer + written,
                    amp_sub_size(buffer_size, written)
                );

                if (ret < 0) {
                    return -1;
                }
                else written += (size_t) ret;
            }

            style_group &= ~layer_style;
            style_pool &= ~layer_style;
        } while (layer_style);
    }

    if (to_stdout) {
        if (amp_stdout(left_bottom_corner, left_bottom_corner_size) < 0) {
            return -1;
        }

        written += left_bottom_corner_size;

        for (long x=0; x<amp->width; ++x) {
            if (amp_stdout(border, border_size) < 0) {
                return -1;
            }

            written += border_size;
        }

        if (amp_stdout(right_bottom_corner, right_bottom_corner_size) < 0) {
            return -1;
        }

        written += right_bottom_corner_size;
    }
    else {
        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written),
            left_bottom_corner
        );

        for (long x=0; x<amp->width; ++x) {
            written += amp_str_append(
                buffer + written, amp_sub_size(buffer_size, written), border
            );
        }

        written += amp_str_append(
            buffer + written, amp_sub_size(buffer_size, written),
            right_bottom_corner
        );
    }

    if (!to_stdout) {
        if (written >= buffer_size || !written) {
            if (buffer_size) {
                *buffer = '\0';
            }
        }
    }

    return written > SSIZE_MAX ? -1 : (ssize_t) written;
}

static inline uint32_t amp_doc_seg_parse_width(const char *str, size_t str_sz) {
    size_t width = 0;
    const char *prev_char = str;
    const char *next_char = amp_str_seg_skip_str(prev_char, str_sz, "╔═");

    if (next_char > prev_char) {
        while (next_char > prev_char) {
            if (++width > UINT32_MAX) return 0;

            prev_char = next_char;
            next_char = amp_str_seg_skip_str(
                prev_char, str_sz - (size_t) (prev_char - str), "═"
            );
        }

        prev_char = next_char;
        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╗"
        );

        if (next_char <= prev_char) {
            width = 0;
        }
    }

    return (uint32_t) width;
}

static inline size_t amp_doc_parse_size(
    const void *data, size_t data_size, uint32_t *canvas_w, uint32_t *canvas_h
) {
    const char *str = (const char *) data;
    const size_t str_sz = data_size;

    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layer_height = 0;

    if (canvas_w) *canvas_w = 0;
    if (canvas_h) *canvas_h = 0;

    for (const char *s = str; *s && s < str + str_sz;) {
        const char *next_line = amp_str_seg_first_line_size(
            s, str_sz - (size_t) (s - str), nullptr
        );

        if (next_line <= s) {
            break;
        }

        if (!width) {
            width = amp_doc_seg_parse_width(s, str_sz - (size_t) (s - str));

            if (!width) {
                return 0; // Invalid or corrupt AMP file detected.
            }

            s = next_line;
            continue;
        }

        const char *prev_char = s;
        const char *next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╚"
        );

        if (next_char > prev_char) {
            // Container end detected.

            height = height < layer_height ? layer_height : height;

            if (canvas_w) *canvas_w = width;
            if (canvas_h) *canvas_h = height;

            return amp_calc_size(width, height);
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╠"
        );

        if (next_char > prev_char) {
            // Layer end detected.

            height = height < layer_height ? layer_height : height;
            layer_height = 0;
            s = next_line;

            continue;
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "║"
        );

        if (next_char == prev_char) {
            return 0; // Invalid or corrupt AMP file detected.
        }

        if (layer_height++ == UINT32_MAX) {
            return 0; // Excessively tall AMP layer detected.
        }

        s = next_line;
    }

    return 0;
}

static inline size_t amp_decode_glyphs(
    struct amp_type *amp, const char *str, size_t str_sz
) {
    uint32_t width = 0;
    uint32_t height = 0;
    long y = 0;

    for (const char *s = str; *s && s < str + str_sz;) {
        const char *next_line = amp_str_seg_first_line_size(
            s, str_sz - (size_t) (s - str), nullptr
        );

        if (next_line <= s) {
            break;
        }

        if (!width) {
            width = amp_doc_seg_parse_width(s, str_sz - (size_t) (s - str));

            if (!width) {
                return 0; // Invalid or corrupt AMP file detected.
            }

            s = next_line;
            continue;
        }

        const char *prev_char = s;
        const char *next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╚"
        );

        if (next_char > prev_char) {
            // Container end detected.
            return amp_calc_size(width, height);
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╠"
        );

        if (next_char > prev_char) {
            // Layer end detected.
            return amp_calc_size(width, height);
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "║"
        );

        if (next_char == prev_char) {
            return 0; // Invalid or corrupt AMP file detected.
        }

        if (height++ == UINT32_MAX) {
            return 0; // Excessively tall AMP file detected.
        }

        long x = 0;

        while (x < width) {
            prev_char = next_char;
            next_char = amp_str_seg_skip_any_utf8_symbol(
                prev_char, str_sz - (size_t) (prev_char - str)
            );

            if (next_char <= prev_char) {
                return 0; // Invalid or corrupt AMP file detected.
            }

            if (amp) {
                // Let's allow decoding in simulation mode when amp is nullptr.
                amp_put_glyph(amp, x, y, prev_char);
            }

            ++x;
        }

        ++y;
        s = next_line;
    }

    return 0;
}

static inline size_t amp_decode_styles(
    struct amp_type *amp, const char *str, size_t str_sz
) {
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layer_height = 0;
    size_t layer = 0;
    long y = 0;
    long first_used_x = LONG_MAX;
    long first_used_y = LONG_MAX;
    long last_used_x = LONG_MIN;
    long last_used_y = LONG_MIN;

    if (amp) {
        memset(amp->canvas.mode.data, 0, amp->canvas.mode.size);
    }

    for (const char *s = str; *s && s < str + str_sz;) {
        const char *next_line = amp_str_seg_first_line_size(
            s, str_sz - (size_t) (s - str), nullptr
        );

        if (next_line <= s) {
            break;
        }

        if (!width) {
            width = amp_doc_seg_parse_width(s, str_sz - (size_t) (s - str));

            if (!width) {
                return 0; // Invalid or corrupt AMP file detected.
            }

            s = next_line;
            continue;
        }

        const char *prev_char = s;
        const char *next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╚"
        );

        if (next_char > prev_char) {
            // Container end detected.

            if (amp
            && first_used_x <= last_used_x
            && first_used_y <= last_used_y) {
                for (long y = first_used_y; y <= last_used_y; ++y) {
                    for (long x = first_used_x; x <= last_used_x; ++x) {
                        uint8_t *mode_data = amp_get_mode_data(amp, x, y);

                        if (!mode_data) {
                            continue;
                        }

                        AMP_STYLE style;
                        memcpy(&style, mode_data, sizeof(style));
                        amp_put_style(amp, x, y, style);
                    }
                }
            }

            height = height < layer_height ? layer_height : height;

            return amp_calc_size(width, height);
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "╠"
        );

        if (next_char > prev_char) {
            // Layer end detected.

            ++layer;
            height = height < layer_height ? layer_height : height;
            layer_height = 0;
            s = next_line;
            y = 0;

            continue;
        }

        next_char = amp_str_seg_skip_str(
            prev_char, str_sz - (size_t) (prev_char - str), "║"
        );

        if (next_char == prev_char) {
            return 0; // Invalid or corrupt AMP file detected.
        }

        if (layer_height++ == UINT32_MAX) {
            return 0; // Excessively tall AMP layer detected.
        }

        if (layer == 0) {
            // Let's skip the text layer as we are only decoding the styles.
            s = next_line;
            continue;
        }

        long x = 0;

        while (x < width) {
            prev_char = next_char;
            next_char = amp_str_seg_skip_any_utf8_symbol(
                prev_char, str_sz - (size_t) (prev_char - str)
            );

            if (next_char <= prev_char) {
                return 0; // Invalid or corrupt AMP file detected.
            }

            if (amp && *prev_char != ' ') {
                // Let's allow decoding in simulation mode when amp is nullptr.

                AMP_STYLE new_style = (
                    amp_lookup_inline_style(prev_char).style
                );

                if (new_style != AMP_STYLE_NONE) {
                    uint8_t *mode_data = amp_get_mode_data(amp, x, y);

                    if (mode_data) {
                        AMP_STYLE old_style;
                        memcpy(&old_style, mode_data, sizeof(old_style));
                        new_style |= old_style;
                        memcpy(mode_data, &new_style, sizeof(new_style));

                        if (x < first_used_x) first_used_x = x;
                        if (y < first_used_y) first_used_y = y;
                        if (x > last_used_x) last_used_x = x;
                        if (y > last_used_y) last_used_y = y;
                    }
                }
            }

            ++x;
        }

        ++y;
        s = next_line;
    }

    return 0;
}

static inline size_t amp_decode(
    struct amp_type *amp, const void *data, size_t data_size
) {
    const char *str = (const char *) data;
    const size_t str_sz = data_size;

    amp_clear(amp);

    size_t decoded_amp_size = amp_decode_styles(amp, str, str_sz);

    if (decoded_amp_size) {
        amp_decode_glyphs(amp, str, str_sz);
    }

    return decoded_amp_size;
}

static inline void amp_draw_ansmap(
    struct amp_type *amp, long x_on_amp, long y_on_amp,
    const struct amp_type *sprite
) {
    for (long dy=0; dy<sprite->height; ++dy) {
        if (y_on_amp + dy >= amp->height) {
            break;
        }

        for (long dx=0; dx<sprite->width; ++dx) {
            if (x_on_amp + dx >= amp->width) {
                break;
            }

            auto const mode = amp_get_mode(sprite, dx, dy);
            const char *glyph = amp_get_glyph(sprite, dx, dy);

            if (mode.bitset.bg == false) {
                if (!glyph || *glyph == '\0') {
                    continue;
                }
            }

            amp_set_mode(amp, x_on_amp + dx, y_on_amp + dy, mode);
            amp_put_glyph(amp, x_on_amp + dx, y_on_amp + dy, glyph);
        }
    }
}

#endif
