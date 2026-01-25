# LibAMP Readme ################################################################

* Home: https://github.com/1Hyena/libamp
* Issue tracker: https://github.com/1Hyena/libamp/issues

In LibAMP, the letters AMP stand for "ANSI Map" (as in ANSI art), and the Lib
prefix indicates that it is a library for the C programming language.


## What is AnsMap ##############################################################

AnsMap (AMP) is a data structure that stores the instructions for printing ANSI
art graphics to the terminal. The AnsMap Library is accompanied by a set of
methods for ansmap construction and for the conversion of ansmap images to ANSI
escape code sequences.

In this context, an ansmap is a digital text-based image represented as a grid
of individual cells called glyphs. Each glyph stores color and style information
to form a complete picture.

The AnsMap Library offers a specialized application programming interface (API)
designed for creating terminal applications and games like multi-user dungeons
(MUDs) and _roguelikes_. It includes the following features:

* **Header-only:** The AnsMap Library is implemented in a single header file
  with no dependencies other than the standard C library.

* **Non-allocating:** LibAMP does not involve any heap memory allocations.

* **UTF8-only:** The library expects UTF-8 encoding of the input text and does
  not attempt to detect Unicode encoding errors.

* **Multi-palette:** The generated ANSI escape sequences can include color codes
  either specific to the standard 16 color palette or to the 24 bit true color
  mode.

* **Text wrapping:** The LibAMP API allows for multiline text printing with the
  user specified maximum line width parameter.

* **Inline style markers:** In rich text printing, style information can be
  embedded into the source text at the location where the style needs to be
  applied.

* **Portable:** LibAMP builds and functions on Linux. It should be relatively
  simple to make it run on most other platforms as long as the platform provides
  the C standard library.

* **Permissive license:** LibAMP is available under the [MIT license](LICENSE).


### The AMP file format ########################################################

LibAMP uses a unique file format that is easily readable by humans, allowing for
convenient image editing using a standard text editor with a fixed-width font.
The recommended file extension for AMP files is `.amp`.

An AMP file is divided into layers, with the first layer dedicated to text
content and required to be present, even if it has zero height (indicating no
text to be printed on the ansmap). Subsequent layers are optional and contain
style markers such as foreground color, background color, and text decoration
specifications. Each style marker occupying the same cell must be represented by
a different layer.

A valid AMP file begins with Unicode box-drawing characters `╔` and `═`. The
number of `═` characters following the first character determines the width of
the ansmap. The sequence is terminated by `╗`.

Subsequent lines must start with `║`, `╠`, or `╚`. If a line starts with `║`,
the count of `║` characters at the beginning of subsequent lines determines the
height of that layer. The layer with the greatest height defines the ansmap's
overall height.

If a line starts with `║`, it must be followed by Unicode characters equal to
the ansmap's width, then another `║`. This sequence defines the contents of one
row in a given layer. Lines starting with `╠` indicate the end of a layer and
the start of a new one if followed by `═` characters equal to the ansmap's width
and a `╣`. Lines starting with `╚` mark the end of a layer and the end of the
AMP file if followed by `═` characters equal to the ansmap's width and a `╝`.

Here is an example of the contents of a valid AMP document:

```
╔══════════════════════════════════════════════════════════════════════════════╗
║             navy background, red foreground, italic, faint italic            ║
║                                                                              ║
╠══════════════════════════════════════════════════════════════════════════════╣
║             NNNNNNNNNNNNNNN  rrrrrrrrrrrrrr  //////  ////////////            ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                      ????????????            ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

The letters and symbols in the second and third box in the example above serve
as style markers for the cells in the first box. Each style marker applies to a
single cell, and their effects can be combined by using multiple style layers.
The position of a style marker on the first layer is determined by its placement
when the style layer is superimposed on the first layer.

For the key of style markers, please refer to the [ExRich](#exrich) example as
it includes the list of available style markers and their definitions.


## Installation ################################################################

Clone the repository and include the header file in your project. Compile using
a C compiler (C23 or later required).


## Using LibAMP ################################################################

The usage of the library can be divided into two main parts: creating and
viewing. The following sections provide a brief overview of each.


### Creating ansmap images #####################################################

To create an ansmap image, you can include the [amp.h](amp.h) header file
directly in your codebase. The library is implemented in a single C header file
for easy integration.

The main functions to use are `amp_init()` and `amp_print_text()`. The
initialization function is necessary to specify the image resolution and data
buffer. The text printing function takes the initialized ansmap pointer as an
argument and prints the desired text on it.

While the initialization of the ansmap data structure typically requires an
external data buffer for storing the image state in memory, it can be omitted.
If omitted, the library will try to use the limited amount of integrated memory
associated with each ansmap. The amount of integrated memory is defined by the
`AMP_BUF_SIZE` macro, which the user can define according to their needs in each
compilation unit.

To determine the size of the external data buffer before initialization, the API
provides the `amp_calc_size()` function, which takes the image resolution as its
arguments.


### Viewing ansmap images ######################################################

To display an ansmap in the terminal, use the `amp_to_ans()` function. It
requires a pointer to the ansmap image structure and a pointer to the memory
location to copy the resulting ANSI escape code sequences that the terminal can
render. If `nullptr` is used for the memory location, the output will be written
to the standard output of the program.


### Examples ###################################################################

To compile all the examples, run the `make` command in the _examples_ directory.

![screenshot](img/make.png "console output of make")


#### ExUnicode #################################################################

The [exunicode](examples/src/exunicode.c) example demonstrates the library's
ability to represent unicode glyphs on the ansmap. In addition, it features text
wrapping.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exunicode.c#L21-L36

![screenshot](img/exunicode.png "console output of exunicode")


#### ExRich ####################################################################

The [exrich](examples/src/exrich.c) example prints the list of available rich
text markers with the respective text samples.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exrich.c#L29-L41

![screenshot](img/exrich.png "console output of exrich")


#### ExEncode ##################################################################

The [exencode](examples/src/exencode.c) program generates rich text on an
ansmap, displays the result in the terminal, and exports the ansmap image as an
AMP document, which is also displayed in the terminal.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exencode.c#L15-L25

![screenshot](img/exencode.png "console output of exencode")


#### ExDecode ##################################################################

The [exdecode](examples/src/exdecode.c) example demonstrates how the
human-readable AMP documents can be imported from memory.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exdecode.c#L7-L40

![screenshot](img/exdecode.png "console output of exdecode")


#### ExAmpFile #################################################################

The [exampfile](examples/src/exampfile.c) example is very similar to
[ExDecode](#exdecode). The only difference is that instead of
deserializing a hardcoded AMP document, the program loads a user specified AMP
file from the file system.

![screenshot](img/exampfile.png "console output of exampfile")


#### Ex24bit ###################################################################

The [ex24bit](examples/src/ex24bit.c) example demonstrates how to use the 24 bit
true color mode when converting the ansmap into a sequence of ANSI escape codes.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L28-L32

![screenshot](img/ex24bit.png "console output of ex24bit")


#### ExMemory ##################################################################

The [exmemory](examples/src/exmemory.c) example shows how to allocate memory
from the heap and use it for the storage of an ansmap image. It then fills the
image with randomly chosen and styled printable ASCII characters.

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L17-L49

![screenshot](img/exmemory.png "console output of exmemory")


### API ########################################################################

* [Colors](#colors)
  - [amp_map_rgb](#amp_map_rgb) (*red*, *green*, *blue*) → `struct amp_color_type`
  - [amp_unmap_rgb](#amp_unmap_rgb) (*color*, &*red*, &*green*, &*blue*)
  - [amp_lookup_color](#amp_lookup_color) (*color index*) → `struct amp_color_type`

* [Ansmap creation](#ansmap-creation)
  - [amp_calc_size](#amp_calc_size) (*width*, *height*) → `size_t`
  - [amp_init](#amp_init) (&*ansmap*, *width*, *height*, &*data*, *data size*) → `size_t`

* [Ansmap properties](#ansmap-properties)
  - [amp_get_palette](#amp_get_palette) (&*ansmap*) → `AMP_PALETTE`
  - [amp_get_width](#amp_get_width) (&*ansmap*) → `uint32_t`
  - [amp_get_height](#amp_get_height) (&*ansmap*) → `uint32_t`
  - [amp_get_glyph](#amp_get_glyph) (&*ansmap*, *x*, *y*) → `const char *`
  - [amp_get_style](#amp_get_style) (&*ansmap*, *x*, *y*) → `AMP_STYLE`
  - [amp_get_bg_color](#amp_get_bg_color) (&*ansmap*, *x*, *y*) → `struct amp_color_type`
  - [amp_get_fg_color](#amp_get_fg_color) (&*ansmap*, *x*, *y*) → `struct amp_color_type`

* [Printing operations](#printing-operations)
  - [amp_clear](#amp_clear) (&*ansmap*)
  - [amp_print_glyph](#amp_print_glyph) (&*ansmap*, *x*, *y*, *style*, &*string*)
  - [amp_print_line](#amp_print_line) (&*ansmap*, *x*, *y*, *style*, *alignment*, &*string*)
  - [amp_snprint_linef](#amp_snprint_linef) (&*amp*, *x*, *y*, *style*, *align*, &*buf*, *buf size*, &*fmt*, *...*) → `ssize_t`
  - [amp_print_text](#amp_print_text) (&*ansmap*, *x*, *y*, *style*, *max width*, *alignment*, &*string*) → `size_t`
  - [amp_snprint_textf](#amp_snprint_textf) (&*amp*, *x*, *y*, *style*, *max width*, *align*, &*buf*, *buf size*, &*fmt*, *...*) → `ssize_t`
  - [amp_print_rich_text](#amp_print_rich_text) (&*ansmap*, *x*, *y*, *style*, *max width*, *alignment*, &*string*) → `size_t`
  - [amp_snprint_rich_textf](#amp_snprint_rich_textf) (&*amp*, *x*, *y*, *style*, *max width*, *align*, &*buf*, *buf size*, &*fmt*, *...*) → `ssize_t`
  - [amp_put_glyph](#amp_put_glyph) (&*ansmap*, *x*, *y*, &*string*) → `const char *`
  - [amp_put_style](#amp_put_style) (&*ansmap*, *x*, *y*, *style*) → `bool`
  - [amp_set_bg_color](#amp_set_bg_color) (&*ansmap*, *x*, *y*, *color*) → `bool`
  - [amp_set_fg_color](#amp_set_fg_color) (&*ansmap*, *x*, *y*, *color*) → `bool`

* [Image I/O](#image-io)
  - [amp_set_palette](#amp_set_palette) (&*ansmap*, palette)
  - [amp_to_ans](#amp_to_ans) (&*ansmap*, &*data*, *data size*) → `ssize_t`
  - [amp_row_to_ans](#amp_row_to_ans) (&*ansmap*, *y*, &*data*, *data size*) → `ssize_t`
  - [amp_clip_to_ans](#amp_clip_to_ans) (&*ansmap*, *x*, *y*, *width*, &*data*, *data size*) → `ssize_t`
  - [amp_parse_size](#amp_parse_size) (&*data*, *data size*, &*width*, &*height*) → `size_t`
  - [amp_decode](#amp_decode) (&*ansmap*, &*data*, *data size*) → `size_t`
  - [amp_encode](#amp_encode) (&*ansmap*, settings, &*data*, *data size*) → `ssize_t`
  - [amp_stdout](#amp_stdout) (&*string*, *string size*) → `ssize_t`


#### Colors ####################################################################

##### amp_map_rgb ##############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L329-L336

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L108)


##### amp_unmap_rgb ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L338-L346


##### amp_lookup_color #########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L348-L353


#### Ansmap creation ###########################################################

##### amp_calc_size ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L127-L133

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L11),
[exmemory](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L17)


##### amp_init #################################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L135-L146

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exhello.c#L9),
[exunicode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exunicode.c#L9),
[exmultiline](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmultiline.c#L9),
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L22),
[exmemory](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L28)


#### Ansmap properties #########################################################

##### amp_get_palette ##########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L391-L394


##### amp_get_width ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L381-L384


##### amp_get_height ###########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L386-L389


##### amp_get_glyph ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L248-L256


##### amp_get_style ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L270-L276


##### amp_get_bg_color #########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L289-L296


##### amp_get_fg_color #########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L309-L316


#### Printing operations #######################################################

##### amp_clear ################################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L148-L151

Examples:
[exrich](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exrich.c#L36)


##### amp_print_glyph ##########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L161-L169

Examples:
[exmemory](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L42)


##### amp_print_line ###########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L171-L181

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exhello.c#L15)


##### amp_snprint_linef ########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L445-L466


##### amp_print_text ###########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L183-L197

Examples:
[exmultiline](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmultiline.c#L15),
[exunicode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exunicode.c#L21)


##### amp_snprint_textf ########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L396-L418


##### amp_print_rich_text ######################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L364-L379


##### amp_snprint_rich_textf ###################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L420-L443

Examples:
[exrich](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exrich.c#L29)


##### amp_put_glyph ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L258-L268


##### amp_put_style ############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L278-L287


##### amp_set_bg_color #########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L298-L307

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L106)


##### amp_set_fg_color #########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L318-L327


#### Image I/O #################################################################

##### amp_set_palette ##########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L153-L159

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L30)


##### amp_to_ans ###############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L199-L212

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exhello.c#L16),
[exunicode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exunicode.c#L38),
[exmultiline](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmultiline.c#L22),
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L31),
[exmemory](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L49)


##### amp_row_to_ans ###########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L214-L228


##### amp_clip_to_ans ##########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L230-L246


##### amp_parse_size ###########################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L490-L504

Examples:
[exdecode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exdecode.c#L20)


##### amp_decode ###############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L506-L517

Examples:
[exdecode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exdecode.c#L30)


##### amp_encode ###############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L468-L488

Examples:
[exencode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exencode.c#L25)


##### amp_stdout ###############################################################

https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/amp.h#L355-L362

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exhello.c#L17),
[exunicode](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exunicode.c#L39),
[exmultiline](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmultiline.c#L23),
[ex24bit](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/ex24bit.c#L32),
[exmemory](https://github.com/1Hyena/libamp/blob/581db1fa1c50e942bf840a3ed133cde3434fa821/examples/src/exmemory.c#L50)


## License #####################################################################

The AnsMap Library has been authored by Erich Erstu and is released under the
[MIT](LICENSE) license.
