# vgg
A C89 standard compliant, single header, nostdlib (no C Standard Library) vector graphics generator (VGG).

<p align="center">
<a href="https://github.com/nickscha/vgg"><img src="assets/vgg.png"></a>
</p>

For more information please look at the "vgg.h" file or take a look at the "examples" or "tests" folder.

> [!WARNING]
> THIS PROJECT IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS PROJECT AT YOUR OWN RISK!

## Quick Start

Download or clone vgg.h and include it in your project.

```C
#include "vgg.h"                /* Vector graphics generator                */
#include "vgg_platform_write.h" /* Optional: OS-Specific write file IO API */

int main() {

    /* vgg.h does not use File IO and just fills the buffer with the executable file data */
    #define BINARY_CAPACITY 4096
    static unsigned char binary_buffer[BINARY_CAPACITY];

    /* Initialize the VGA writer */
    vgg_svg_writer w = {binary_buffer, BINARY_CAPACITY, 0};

    vgg_color color_green = {0, 255, 0};

    vgg_rect rect = {0};

    /* General header fields */
    rect.header.id = 0;
    rect.header.type = VGG_TYPE_RECT;
    rect.header.color_fill = color_green;
    rect.header.data_fields_count = 0;

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
    vgg_platform_write("test.svg", w.buffer, (unsigned long)w.length);

    return 0;
}
```

## Run Example: nostdlib, freestsanding

In this repo you will find the "examples/vgg_win32_nostdlib.c" with the corresponding "build.bat" file which
creates an executable only linked to "kernel32" and is not using the C standard library and executes the program afterwards.

## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.
