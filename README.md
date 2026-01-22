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

* **Text wrapping:** The LibAMP API allows for multiline text drawing with the
  user specified maximum line width parameter.

* **Inline style markers:** In rich text printing, style information can be
  embedded into the source text at the location where the style needs to be
  applied.

* **Portable:** LibAMP builds and functions on Linux. It should be relatively
  simple to make it run on most other platforms as long as the platform provides
  the C standard library.

* **Permissive license:** LibAMP is available under the [MIT license](LICENSE).


## Installation ################################################################

Clone the repository and include the header file in your project. Compile using
a C compiler (C23 or later required).


## Using LibAMP ################################################################

The usage of the library can be divided into two main parts: drawing and
rendering. The following sections provide a brief overview of each.


### Drawing ansmap images ######################################################

To create an ansmap image, you can include the [amp.h](amp.h) header file
directly in your codebase. The library is implemented in a single C header file
for easy integration.

The main functions to use for drawing are `amp_init()` and `amp_draw_text()`.
The initialization function is necessary to specify the image resolution and
data buffer. The text drawing function takes the initialized ansmap pointer as
an argument and prints the desired text on it.

While the initialization of the ansmap data structure typically requires an
external data buffer for storing the image state in memory, it can be omitted.
If omitted, the library will try to use the limited amount of integrated memory
associated with each ansmap. The amount of integrated memory is defined by the
`AMP_BUF_SIZE` macro, which the user can define according to their needs in each
compilation unit.

To determine the size of the external data buffer before initialization, the API
provides the `amp_calc_size()` function, which takes the image resolution as its
arguments.


### Rendering ansmap images ####################################################

To display an ansmap in the terminal, use the `amp_to_ans()` function. It
requires a pointer to the ansmap image structure and a pointer to the memory
location to copy the result. If `nullptr` is used for the memory location, the
output will be written to the standard output of the program.


### Examples ###################################################################

To compile all the examples, run the `make` command in the _examples_ directory.

![screenshot](img/make.png "console output of make")


#### ExUnicode #################################################################

The [exunicode](examples/src/exunicode.c) example demonstrates the library's
ability to represent unicode glyphs on the ansmap. In addition, it features text
wrapping.

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exunicode.c#L21-L36

![screenshot](img/exunicode.png "console output of exunicode")


#### ExRich ####################################################################

The [exrich](examples/src/exrich.c) example prints the list of available rich
text markers with the respective text samples.

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exrich.c#L46-L51

![screenshot](img/exrich.png "console output of exrich")


#### Ex24bit ###################################################################

The [ex24bit](examples/src/ex24bit.c) example demonstrates how to use the 24 bit
true color mode when converting the ansmap into a sequence of ANSI escape codes.

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L28-L32

![screenshot](img/ex24bit.png "console output of ex24bit")


#### ExMemory ##################################################################

The [exmemory](examples/src/exmemory.c) example shows how to allocate memory
from the heap and use it for the storage of an ansmap image. It then fills the
image with randomly chosen and styled printable ASCII characters.

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L17-L49

![screenshot](img/exmemory.png "console output of exmemory")


### API ########################################################################

* [Colors](#colors)
  - [amp_map_rgb](#amp_map_rgb)(`red`, `green`, `blue`)
  - [amp_unmap_rgb](#amp_unmap_rgb)(`color`, &`red`, &`green`, &`blue`)
  - [amp_lookup_color](#amp_lookup_color)(`color_index`)

* [Ansmap creation](#ansmap-creation)
  - [amp_calc_size](#amp_calc_size)
  - [amp_init](#amp_init)

* [Ansmap properties](#ansmap-properties)
  - [amp_get_palette](#amp_get_palette)
  - [amp_get_width](#amp_get_width)
  - [amp_get_height](#amp_get_height)
  - [amp_get_glyph](#amp_get_glyph)
  - [amp_get_style](#amp_get_style)
  - [amp_get_bg_color](#amp_get_bg_color)
  - [amp_get_fg_color](#amp_get_fg_color)

* [Printing operations](#printing-operations)
  - [amp_set_palette](#amp_set_palette)
  - [amp_clear](#amp_clear)
  - [amp_print_glyph](#amp_print_glyph)
  - [amp_print_line](#amp_print_line)
  - [amp_print_text](#amp_print_text)
  - [amp_print_rich_text](#amp_print_rich_text)
  - [amp_put_glyph](#amp_put_glyph)
  - [amp_put_style](#amp_put_style)
  - [amp_set_bg_color](#amp_set_bg_color)
  - [amp_set_fg_color](#amp_set_fg_color)

* [Image I/O](#image-io)
  - [amp_to_ans](#amp_to_ans)
  - [amp_row_to_ans](#amp_row_to_ans)
  - [amp_clip_to_ans](#amp_clip_to_ans)
  - [amp_stdout](#amp_stdout)


#### Colors ####################################################################

##### amp_map_rgb ##############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L318-L325

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L108)


##### amp_unmap_rgb ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L327-L335


##### amp_lookup_color #########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L337-L342


#### Ansmap creation ###########################################################

##### amp_calc_size ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L116-L122

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L11),
[exmemory](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L17)


##### amp_init #################################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L124-L135

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exhello.c#L9),
[exunicode](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exunicode.c#L9),
[exmultiline](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmultiline.c#L9),
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L22),
[exmemory](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L28)


#### Ansmap properties #########################################################

##### amp_get_palette ##########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L380-L383


##### amp_get_width ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L370-L373


##### amp_get_height ###########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L375-L378


##### amp_get_glyph ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L237-L245


##### amp_get_style ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L259-L265


##### amp_get_bg_color #########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L278-L285


##### amp_get_fg_color #########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L298-L305


#### Printing operations #######################################################

##### amp_set_palette ##########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L142-L148

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L30)


##### amp_clear ################################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L137-L140

Examples:
[exrich](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exrich.c#L37)


##### amp_print_glyph ##########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L150-L158

Examples:
[exmemory](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L41)


##### amp_print_line ###########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L160-L170

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exhello.c#L15)


##### amp_print_text ###########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L172-L186

Examples:
[exmultiline](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmultiline.c#L15),
[exunicode](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exunicode.c#L21)


##### amp_print_rich_text ######################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L353-L368

Examples:
[exrich](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exrich.c#L46)


##### amp_put_glyph ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L247-L257


##### amp_put_style ############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L267-L276


##### amp_set_bg_color #########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L287-L296

Examples:
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L106)


##### amp_set_fg_color #########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L307-L316


#### Image I/O #################################################################

##### amp_to_ans ###############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L188-L201

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exhello.c#L16),
[exunicode](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exunicode.c#L38),
[exmultiline](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmultiline.c#L22),
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L31),
[exmemory](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L49)


##### amp_row_to_ans ###########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L203-L217


##### amp_clip_to_ans ##########################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L219-L235


##### amp_stdout ###############################################################

https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/amp.h#L344-L351

Examples:
[exhello](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exhello.c#L17),
[exunicode](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exunicode.c#L39),
[exmultiline](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmultiline.c#L23),
[ex24bit](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/ex24bit.c#L32),
[exmemory](https://github.com/1Hyena/libamp/blob/bd41b077f472a99e9f66f23d7d12feb89461ef46/examples/src/exmemory.c#L50)


## License #####################################################################

The AnsMap Library has been authored by Erich Erstu and is released under the
[MIT](LICENSE) license.
