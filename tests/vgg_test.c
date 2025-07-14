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

void vgg_test_data_field(void)
{
  char value_buffer[32];
  vgg_data_field f1 = vgg_data_field_create_float("weight", 20.0f, 4, value_buffer);

  printf("%s, %s\n", f1.key, f1.value);
}

void vgg_test_color_map_linear(void)
{
  vgg_color start = {144, 224, 239}; /* Start (light teal): 144, 224, 239 */
  vgg_color end = {255, 85, 0};      /*  End (dark orange): 255,  85,   0 */

  vgg_color current;

  current = vgg_color_map_linear(0.0, 0.0, 1.0, start, end);
  assert(current.r == 144 && current.g == 224 && current.b == 239);

  current = vgg_color_map_linear(1.0, 0.0, 1.0, start, end);
  assert(current.r == 255 && current.g == 85 && current.b == 0);
}

void vgg_test_svg_write_rect(void)
{
/* vgg.h does not use File IO and just fills the buffer with the executable file data */
#define BINARY_CAPACITY 4096
  static unsigned char binary_buffer[BINARY_CAPACITY];

  /* Initialize the VGA writer */
  vgg_svg_writer w = {binary_buffer, BINARY_CAPACITY, 0};

  vgg_color color_green = {0, 255, 0};

  vgg_rect rect = {0};

  vgg_data_field data_field = {"weight", "20.0"};
  vgg_data_field data_field2 = {"num_lines_of_code", "165"};
  vgg_data_field data_fields[2];

  data_fields[0] = data_field;
  data_fields[1] = data_field2;

  /* General header fields */
  rect.header.id = 0;
  rect.header.type = VGG_TYPE_RECT;
  rect.header.color_fill = color_green;
  rect.header.data_fields = data_fields;
  rect.header.data_fields_count = 2;

  /* Rect specific fields */
  rect.x = 0.0;
  rect.y = 0.0;
  rect.width = 800;
  rect.height = 300;

  vgg_svg_start(&w, "vgg_svg", 800, 300);
  {
    vgg_svg_element_add(&w, (vgg_header *)&rect);
  }
  vgg_svg_end(&w);

  /* By default vgg itself does not use file IO to stay nostdlib and platform independant                                */
  /* If you want a small file write implementation (nostdlib but platform dependant) than include "vgg_platform_write.h" */
  vgg_platform_write("test_rect.svg", w.buffer, (unsigned long)w.length);
}

int main(void)
{
  vgg_test_data_field();
  vgg_test_color_map_linear();
  vgg_test_svg_write_rect();

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
