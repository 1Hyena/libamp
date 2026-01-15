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


### API ########################################################################

https://github.com/1Hyena/libamp/blob/8ca29b9f924a84ad0e013ac825764ad37620a085/amp.h#L113-237


## License #####################################################################

The AnsMap Library has been authored by Erich Erstu and is released under the
[MIT](LICENSE) license.
