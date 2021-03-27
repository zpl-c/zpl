<div align="center">
    <a href="https://github.com/zpl-c/zpl"><img src="https://user-images.githubusercontent.com/2182108/111983468-d5593e80-8b12-11eb-9c59-8c78ecc0504e.png" alt="zpl" /></a>
</div>

<br />

<div align="center">
    <a href="https://github.com/zpl-c/zpl/actions"><img src="https://img.shields.io/github/workflow/status/zpl-c/zpl/tester?label=Tests&style=for-the-badge" alt="Build status" /></a>
    <a href="https://discord.gg/2fZVEym"><img src="https://img.shields.io/discord/354670964400848898?color=7289DA&style=for-the-badge" alt="discord" /></a>
</div>

<br />
<div align="center">
  C99 cross-platform header-only library that offers a powerful toolkit to accelerate your development progress.
</div>

<div align="center">
  <sub>
    Brought to you by <a href="https://github.com/zaklaus">@zaklaus</a>,
     <a href="https://github.com/inlife">@inlife</a>,
    and <strong>contributors</strong>
  </sub>
</div>

# Introduction
We have created the library to simplify the development process under C/C++ language, which offers a commonly used set of features that C developers often re-invent themselves. Apart from helper methods that replace/extend the C standard library, this toolkit also consists of modules that are very helpful in broad areas of expertise. The most notable is the JSON5 parser, math library, flexible file API, or various hashing algorithms.

Library is cross-platform and currently works on **i386**, **amd64** and some **ARM** architectures. It has been tested on **Windows**, **UNIX-like systems**, **iOS**, **Emscripten** and **Android**.
We're trying to expand the compatibility, but we need your help! If you have a device you want to test zpl on, please let us know about your experience, and we can try to make it work together.

## Who uses this library?

* [librg](https://github.com/zpl-c/librg) - Making multi-player simpler since 2017. Single-header cross-platform world replication library in pure C99.

# How to obtain this library?

There are several options in getting hands-on zpl:

## 1. Via CLI (the simplest option)
```sh
curl -L zpl.pw/fetch > zpl.h
# OR
wget zpl.pw/fetch -O zpl.h
```

This approach will download the latest release of zpl with everything prepared for you.

## 2. Via GitHub releases page
* Navigate to the [releases page](https://github.com/zpl-c/zpl/releases) of the zpl repository and pick the version you want to use. Each release contains the distributed version of zpl for you to use easily.

## 3. Cloning the repository
* Clone the repository by pressing the **Clone or download** button for instructions or use your terminal to clone:
```sh
git clone https://github.com/zpl-c/zpl.git
```

We use this method to develop zpl as it contains all the development sources that are easy to modify and expand, but it is not suitable for use in production.

Please follow the [CONTRIBUTING.md](.github/CONTRIBUTING.md) guide to learn how to contribute to the project.

# Modules

zpl consists of modules that we pack to various distributions. By default, it offers most of the modules from the go.
It also offers a **nano** distribution consisting only of essential parts that form the basis of the library, those are:
* **Macro helpers** - This module contains many useful macros helpful for debugging and development itself.
* **Memory** - Consists of pointer arithmetic methods, virtual memory management, and custom memory allocators.
* **Collections** - Consists of C++-template-like macros that define containers for any type. These collections are C-friendly and accessible using `de-reference` or `[]` operators. These are buffer, array, linked-list, ring buffer.
* **String** - Offers methods for c-string manipulation and a string library that is c-string read-only compatible.
* **Hashtable** - An instantiated hashtable implementation that works for any type defined.
* **File** - File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.
* **TAR archiving** - Provides a simple API to archive files or read existing archives.
* **Memory streamer** - This allows us to use the file API to manipulate the memory. (e.g., parse media files from memory, export JSON5 object to a string, ...)
* **Print** - Re-implementation of printf methods.
* **Time** - Helper methods for retrieving the current time in many forms under different precisions.
* **Random** - Fast and simple RNG library.
* **Sorting** - Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains a simple implementation of binary search and an easy-to-use API to define your comparators.
* **Miscellaneous** - Methods that don't belong anywhere but are still very useful on many occasions.

From which we also made a **pico** distribution that only contains: **Macro helpers**, **Memory** and **Collections** modules. Useful in embedded environments where you know exactly which modules you want to use. As always, you can easily enable additional modules as you'd like, do note that not all combinations were tested and might even cause issues when the **pico** distribution is enabled. There is no ability to enable specific core submodules within the **pico** distribution; however, consider using the **nano** distribution in that case.

Additionally, zpl also contains these additional modules that build upon the core library itself:
* **Threading** - This module features common threading and blocking principles. It contains thread merge operation based on stb_sync, as well as CPU affinity management.
* **Regex** - Port of gb_regex with several bugfixes applied. That is a simple regex library and is fast to perform.
* **DLL** - Helper methods for loading a dynamic library. It also offers the ability to load a procedure address.
* **Timer** - A simple to use callback-based timer library.
* **Hashing** - Several hashing methods useful in many domains. Contains: base64, adler32, crc32/64, fnv32/64/a and murmur32/64
* **JSON5 parser** - Easy to use and very fast JSON5 parser that can easily load 50 megabytes of JSON content under half a second. It also contains a simple JSON5 writer and acts as a good library for handling config files.
* **Opts** - Opts is a CLI options parser. It can parse flags, switches, and arguments from the command line and offers an easy way to express input errors and display a help screen.
* **Process** - Gives you the ability to create a new process, wait for it to end, or terminate it. It also exposes standard I/O with configurable options.
* **Jobs system** - Can set up a batch of workers which use thread-pool pattern to handle async tasks without the unnecessary threading overhead.
* **Co-routines** - This module implements co-routines feature for C11.
* **Math** - OpenGL game dev friendly library for math.

## Examples
We cover many of these modules with example code you can explore at [apps/examples](https://github.com/zpl-c/zpl/tree/master/code/apps/examples) folder. They serve as a good starting point to better understand how the library works. Have a look at this base64 text encoder:

```c
#define ZPL_IMPL
#define ZPL_NANO
#define ZPL_ENABLE_OPTS
#define ZPL_ENABLE_HASHING
#include <zpl.h>

void exit_with_help(zpl_opts *opts);

int main(int argc, char **argv) {
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);
    zpl_opts_add(&opts, "s", "string", "input string.", ZPL_OPTS_STRING);
    zpl_opts_positional_add(&opts, "string");
    zpl_b32 ok = zpl_opts_compile(&opts, argc, argv);
    if (!ok || !zpl_opts_positionals_filled(&opts))
        exit_with_help(&opts);

    zpl_string input = zpl_opts_string(&opts, "string", 0);
    zpl_u8 *encoded_str = zpl_base64_encode(zpl_heap(), cast(void*)input, zpl_string_length(input));
    zpl_printf("Original: %s\nEncoded: %s\n", input, encoded_str);

    zpl_mfree(encoded_str);
    zpl_opts_free(&opts);
    return 0;
}

void exit_with_help(zpl_opts *opts) {
    zpl_opts_print_errors(opts);
    zpl_opts_print_help(opts);
    zpl_exit(-1);
}
```

# Frequently Asked Questions

**What is this library based on?**

zpl is a fork of a library made by [@gingerBill](https://github.com/gingerBill) called [gb](https://github.com/gingerBill/gb) that we've decided to expand and rewrite
to fit our needs better. Although many parts of the library still stay faithful to their original, a significant amount of work shaped the library into what we present now.

**Can I contribute to the project?**

Yes, indeed. This project is dual-licensed according to LICENSE. You are free to fork it, contribute to it, or even sell it as you see fit.

**Can I submit suggestions?**

Indeed, We'd also gladly discuss those with you on Discord, if possible.
