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

#### ex24bit ###################################################################

The [ex24bit](examples/src/ex24bit.c) example demonstrates how to use the 24 bit
true color mode when converting the ansmap into a sequence of ANSI escape codes.

https://github.com/1Hyena/libamp/blob/ff653ed59d8848de730c945f1c08f74d2c064d86/examples/src/ex24bit.c#L28-L32

![screenshot](img/ex24bit.png "console output of ex24bit")


#### exmemory ##################################################################

The [exmemory](examples/src/exmemory.c) example shows how to allocate memory
from the heap and use it for the storage of an ansmap image. It then fills the
image with randomly chosen and styled printable ASCII characters.

https://github.com/1Hyena/libamp/blob/26088431a14ee16e3c196e4fd9fa4824c272fd17/examples/src/exmemory.c#L17-L49

![screenshot](img/exmemory.png "console output of exmemory")


### API ########################################################################

#### amp_calc_size #############################################################

https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L114-L120

Examples:
* [ex24bit](#ex24bit)
* [exmemory](#exmemory)


#### amp_init ##################################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L122-L133


#### amp_clear #################################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L135-L138


#### amp_set_palette ###########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L140-L146


#### amp_draw_glyph ############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L148-L156


#### amp_draw_text #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L158-L168


#### amp_draw_multiline_text ###################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L170-L184


#### amp_to_ans ################################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L186-L199


#### amp_row_to_ans ############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L201-L215


#### amp_row_cut_to_ans ########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L217-L233


#### amp_get_glyph #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L235-L243


#### amp_put_glyph #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L245-L255


#### amp_get_style #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L257-L263


#### amp_put_style #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L265-L274


#### amp_get_bg_color ##########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L276-L283


#### amp_set_bg_color ##########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L285-L294


#### amp_get_fg_color ##########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L296-L303


#### amp_set_fg_color ##########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L305-L314


#### amp_map_rgb ###############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L316-L323


#### amp_unmap_rgb #############################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L325-L333


#### amp_lookup_color ##########################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L335-L340


#### amp_stdout ################################################################

  https://github.com/1Hyena/libamp/blob/d6aaab19af4b7502491d82f01f4f925b7a2a2055/amp.h#L342-L349


## License #####################################################################

The AnsMap Library has been authored by Erich Erstu and is released under the
[MIT](LICENSE) license.
