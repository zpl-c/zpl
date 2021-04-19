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
  C99 cross-platform header-only library oriented towards improving the coding experience.
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

| Name | Description | Test Coverage | Example Coverage |
| ------ | ---------- | :----: | :----: |
| **Memory** | Low-level memory management and allocation strategy models. | 🟡 | ✅ |
| **Collections** | Versatile set of collections: `array`, `buffer`, `linked list`, `ring buffer`. | 🔴 | ✅ |
| **String** | Set of helpful string manipulation methods. | 🔴 | ✅ |
| **String Libary** | C-friendly string library. | 🔴 | ✅ |
| **Hashtable** | Instantiated hashtable implementation that works with any type. | 🔴 | ✅ |
| **File** | File I/O operations forming a basis for other modules. | 🔴 | ✅ |
| **File System** | Path and folder structure manipulation methods. | 🔴 | ✅ |
| **TAR Archive** | Ability to archive files or analyze/unpack them. | 🔴 | ✅ |
| **Memory Streamer** | Memory-mapped file I/O operations. | ✅ | ✅ |
| **Print** | Re-implementation of various printf-family methods. | ✅ | ✅ |
| **Time** | Helper methods for retrieving the current time in many forms under different precisions. | ✅ | ✅ |
| **Random** | Fast and simple RNG library. | 🔴 | ✅ |
| **Sorting** | Various sorting and searching algorithms. | 🔴 | ✅ |
| **Threading** | Threading, and blocking models, thread merge operation based on stb_sync, as well as CPU affinity management. | 🔴 | ✅ |
| **Regex** | Regular expressions library. | 🔴 | ✅ |
| **DLL** | Cross-platform methods for loading dynamic libraries. | 🔴 | ✅ |
| **Timer** | Callback-based primitive timer library. | 🔴 | ✅ |
| **Hashing** | Various hashing methods. Contains: `base64`, `adler32`, `crc32/64`, `fnv32/64/a` and `murmur32/64` | ✅ | ✅ |
| **Text Parsers** | Various text parsers for different formats that offer cross-language transformations. Currently supported: `JSON5/SJSON`, `CSV`. | ✅ | ✅ |
| **Options** | CLI options parser. Parsing flags, switches, and arguments from the command line. | 🔴 | ✅ |
| **Process** | Primitives for low-level process management. | 🔴 | ✅ |
| **Jobs System** | Asynchronous task-based scheduling system. | 🔴 | ✅ |
| **Co-routines** | LUA-inspired module implementing co-routines feature for C11. | 🔴 | ✅ |
| **Math** | Gamedev friendly library for math. | 🔴 | ✅ |
| **Miscellaneous** | Other valuable methods that are part of the core distribution. | ✅ | ✅ |

## Distributions

All distributions are defined at compile-time. You can always opt-in to any distribution kind without a need to maintain different copies of the library.

### Default

zpl enables all of its modules by default, which allows you to make full use of the library effortlessly.

### ZPL_NANO

The **nano** distribution provides the core parts of the library. It omits some specialized modules in favor of broader compatibility, and that also makes the library lightweight.

### ZPL_PICO
We've also made a **pico** distribution that only contains: **Memory** and **Collections** modules. There is no ability to enable specific core submodules within the **pico** distribution; however, consider using the **nano** distribution in that case.

### Custom distributions

zpl also allows you to enable/disable various modules at will, allowing you to create your distribution suiting your needs.

# Examples
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

Yes, indeed. This project is dual-licensed according to [LICENSE](LICENSE). You are free to fork it, contribute to it, or even sell it as you see fit.

**Can I submit suggestions?**

Indeed, we'd also gladly discuss those with you on Discord, if possible.
