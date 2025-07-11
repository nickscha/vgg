/* vgg.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) executable file/format builder (VGG).

This Test class defines cases to verify that we don't break the excepted behaviours in the future upon changes.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../vgg.h"                /* Vector graphics generator                        */
#include "../vgg_platform_write.h" /* Optional: OS-Specific write file implementations */

#include "test.h" /* Simple Testing framework */

int main(void)
{

/* vgg.h does not use File IO and just fills the buffer with the executable file data */
#define BINARY_CAPACITY 4096
  static unsigned char binary_buffer[BINARY_CAPACITY];

  /* Initialize the VGA writer */
  vgg_svg_writer w = {binary_buffer, BINARY_CAPACITY, 0};

  /* Start the SVG section for an 100x100 area */
  vgg_svg_start(&w, 100, 100);
  {
    vgg_svg_color color_red = {255, 0, 0};
    vgg_svg_color color_green = {0, 255, 0};
    vgg_svg_color color_blue = {0, 0, 255};

    vgg_svg_data_field data_field = {"weight", "20.0"};
    vgg_svg_data_field data_field2 = {"num_lines_of_code", "165"};
    vgg_svg_data_field data_fields[2];
    data_fields[0] = data_field;
    data_fields[1] = data_field2;

    vgg_svg_add_rect(&w, 1, 0, 0, 50, 50, color_red, 0, 0);
    vgg_svg_add_rect(&w, 2, 0, 50, 50, 50, color_green, 0, 0);
    vgg_svg_add_rect(&w, 3, 50, 0, 50, 50, color_blue, 0, 0);
    vgg_svg_add_rect(&w, 4, 50, 50, 50, 50, color_red, data_fields, 2);
  }
  vgg_svg_end(&w);

  /* By default vgg itself does not use file IO to stay nostdlib and platform independant                                */
  /* If you want a small file write implementation (nostdlib but platform dependant) than include "vgg_platform_write.h" */
  vgg_platform_write("test.svg", w.buffer, (unsigned long)w.length);

  assert(1 == 1);

  return 0;
}

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
