<div align="center">
    <a href="https://github.com/zpl-c/zpl"><img src="https://user-images.githubusercontent.com/9026786/103413377-8afe9c00-4b79-11eb-9cda-1caa4800b487.png" alt="zpl" /></a>
</div>

<div align="center">
    <a href="https://github.com/zpl-c/zpl/actions"><img src="https://img.shields.io/github/workflow/status/zpl-c/zpl/tester?label=Tests&style=for-the-badge" alt="Build status" /></a>
    <a href="https://discord.gg/2fZVEym"><img src="https://img.shields.io/discord/354670964400848898?color=7289DA&style=for-the-badge" alt="discord" /></a>
</div>

<br />
<div align="center">
  C99 cross-platform header-only library that offers powerful toolkit to accelerate your development progress.
</div>

<div align="center">
  <sub>
    Brought to you by <a href="https://github.com/zaklaus">@zaklaus</a>,
     <a href="https://github.com/inlife">@inlife</a>,
    and <strong>contributors</strong>
  </sub>
</div>

# Introduction
It's been created to simplify development process under C/C++ language and offers commonly used set of features that C developers often re-invent or search libraries for. Apart from helper methods that replace/extend C standard library, this toolkit also consists of modules that are very helpful in specific areas of expertise, such as graph culling algorithms, JSON5 parser, OpenGL-friendly math library as well as OpenGL helper module and many more...

Library is cross-platform and currently works on **i386**, **amd64** and some **ARM** architectures. It has been tested on **Windows**, **UNIX-like systems**, **iOS**, **Emscripten** and **Android**.
We're trying to expand the compatibility, but we need your help! If you have a device you want to test ZPL on, feel free to let us know about your experience and we can try to make it work together.

| Platform / Result 	| Windows               	| macOS      	| Linux      	| iOS   	| Android 	| Raspberry Pi 	| OpenBSD 	| FreeBSD    	| Emscripten 	|
|-------------------	|-----------------------	|------------	|------------	|-------	|---------	|--------------	|---------	|------------	|------------	|
|         ✅         	| msvc, mingw, clang-cl 	| gcc, clang 	| gcc, clang 	| clang 	|  clang  	|  gcc, clang 	|         	| gcc, clang 	|            	|
|         ☑️         	|                       	|            	|            	|       	|         	|              	|  clang  	|            	|            	|
|         ❔         	|                       	|            	|            	|       	|   gcc   	|           	|   gcc   	|            	|            	|
|         🔴         	|                       	|            	|            	|       	|         	|              	|         	|            	|    emcc    	|

#### Legend:

* ❔ - Library was not tested on this platform/compiler yet
* ✅ - Library successfully compiles, and all tests are executed properly
* ☑️ - compiles with limited features only. *
* 🔴 - compilation/runtime faults.
<br/><br/>

*This platform's support is unfinished and might lack some features or degree of functionality compared to fully supported platforms. See [Platform Debt](https://github.com/zpl-c/zpl/blob/master/.github/PLATFORM_DEBT.md) to find out which features are missing out for your platform.


## Who uses this library?

* [librg](https://github.com/zpl-c/librg) - Making multi-player simpler since 2017. Single-header cross-platform world replication library in pure C99.

# How to get this library?

There are several options in getting hands on ZPL:

## 1. Via CLI (the simplest option):
```sh
curl -L zpl.pw/fetch > zpl.h
# OR
wget zpl.pw/fetch -O zpl.h
```

This will download the latest release of ZPL with everything prepared for you.

## 2. Via GitHub releases page:
* Navigate to the [releases page](https://github.com/zpl-c/zpl/releases) of the ZPL repository and simply pick the version you want to use. Each release contains distributed version of ZPL for you to use easily.

## 3. Cloning the repository:
* Simply clone the repository by pressing the **Clone or download** button for instructions or simply use your terminal to clone:
```sh
git clone https://github.com/zpl-c/zpl.git
```

This method is used by us to develop ZPL as it contains all the development sources that are easy to modify and expand, but it is not suitable for vendoring.

Please follow the [CONTRIBUTING.md](.github/CONTRIBUTING.md) guide to learn how to contribute to the project.

# Table of Contents

ZPL consists of modules that are packed to various distributions. By default, ZPL offers most of the modules from the go.
It also offers a **nano** distribution consisting only of essential parts that form the basis of the library, those are:
* **Macro helpers** - This module contains many useful macros helpful for debugging as well as development itself.
* **Memory** - Consists of pointer arithmetic methods, virtual memory management and custom memory allocators.
* **Collections** - Consists of C++-template-like macros that define containers for any type. All of these collections are C friendly and accessible using `de-reference` or `[]` operators. These are: buffer, array, linked-list, ring buffer.
* **String** - Offers methods for c-string manipulation, but also a string library that is c-string read-only compatible.
* **Hashtable** - An instantiated hashtable implementation which works for any type defined.
* **File** - File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.
* **Memory streamer** - Allows us to use the file API to manipulate the memory. (e.g. parse media files from memory, export JSON5 object to string, ...)
* **Print** - Re-implementation of printf methods.
* **Time** - Helper methods for retrieving the current time in many forms under different precisions.
* **Random** - Fast and simple RNG library.
* **Sorting** - Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains simple implementation of binary search, as well as an easy to use API to define your own comparators.
* **Miscellaneous** - Methods that don't belong anywhere but are still very useful in many occasions.

From which we also made a **pico** distribution that only contains: **Macro helpers**, **Memory** and **Collections** modules. Useful in embedded environments where you know exactly which modules you want to make use of. As always, you can easily enable additional modules as you'd like, do note that not all combinations were tested and might even cause issues when the **pico** distribution is enabled. There is no ability to enable specific core submodules within the **pico** distribution however, consider using the **nano** distribution in that case.

Additionally, ZPL also contains these additional modules that build upon the core itself:
* **Threading** - This module features common threading and blocking principles. It contains thread merge operation based on stb_sync, as well as CPU affinity management.
* **Regex** - Port of gb_regex with several bugfixes applied. This is a simple regex library and is fast to perform.
* **DLL** - Helper methods for loading a dynamic library. It also offers an ability to load a procedure address.
* **Timer** - A simple to use callback-based timer library.
* **Hashing** - Several hashing methods useful in many domains. Contains: base64, adler32, crc32/64, fnv32/64/a and murmur32/64
* **JSON5 parser** - Easy to use and very fast JSON5 parser that can easily load 50 megabytes of JSON content under half a second. It also contains simple JSON5 writer and acts as a good library for handling config files.
* **Opts** - Opts is a CLI options parser, it can parse flags, switches and arguments from command line and offers an easy way to express input errors as well as the ability to display help screen.
* **Process** - Gives you the ability to create a new process, wait for it to end or terminate it. It also exposes standard I/O with configurable options.
* **Jobs system** - Can set up a batch of workers which use thread-pool pattern to handle async tasks without the unecessary threading overhead.
* **Co-routines** - This module implements co-routines feature for C11.
* **Math** - OpenGL gamedev friendly library for math.

# Example Usage
In this example, I'll show you how to write a simple JSON5 benchmark tool by using ZPL only.

First, I recommend looking at [zpl.h](https://github.com/zpl-c/zpl/releases/latest) header file from the releases, which describes how to use the library. Now you know, that to use zpl.h in your project, you have to define `ZPL_IMPLEMENTATION` exactly in **ONE SOURCE** file **BEFORE** including the zpl.h file itself to successfully embed it.

Afterwards, we need to deal with file loading, simply navigate to the `code` folder and find the respective module [file.h](https://github.com/zpl-c/zpl/blob/master/code/header/core/file.h)

As you can see, each module is contained within its own header/source file. These are bundled together on each release. When we develop ZPL, we include [code/zpl.h](https://github.com/zpl-c/zpl/blob/master/code/zpl.h), as it allows us to have full syntax and semantics support while coding the library. However, as an end user, you can use ZPL from the releases page, as it contains everything bundled together and ready to be used within the project.

File module takes care of necessary file i/o operations. Write a code to read `test.json5` file (you can use `zpl_file_read_contents`) and try to print its content (either use libc's printf or methods from [print.h](https://github.com/zpl-c/zpl/blob/master/code/header/core/print.h)) Check [code/apps](https://github.com/zpl-c/zpl/blob/master/code/apps/examples/) folder for code examples.

Done? Great! Now we need to parse this file, but how? Well guess what, [json.h](https://github.com/zpl-c/zpl/blob/master/code/header/json.h) is exactly what you're looking for! Now you might wonder, you can parse JSON5 files...

But what use is it for a benchmark tool if it doesn't even let you know how long the process took? It is time (pun intended) to visit [time.h](https://github.com/zpl-c/zpl/blob/master/code/header/core/time.h) file now, capture 2 timestamps, one before, another after the operation happened and the difference is your time you can display to user. Or just check out code examples in test folder.

What's left? We can read a specific JSON5 file, parse it and display the time it took to do so. Did I say.. specific? How about we let the user customise the options on the command line?

Visit [opts.h](https://github.com/zpl-c/zpl/blob/master/code/header/opts.h) and get to know it. As always, test folder can be useful in this case.

Actually, the following snippet comes from the [json_benchmark.c](https://github.com/zpl-c/zpl/blob/master/code/apps/examples/json_benchmark.c) test file:

```c
#define ZPL_IMPLEMENTATION
#define ZPL_NANO
#define ZPL_ENABLE_OPTS
#include <zpl.h>

int main(int argc, char **argv)
{
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);

    zpl_opts_add(&opts, "?", "help", "the HELP section", ZPL_OPTS_FLAG);
    zpl_opts_add(&opts, "f", "foo", "the test *foo* entry.", ZPL_OPTS_STRING);
    zpl_opts_add(&opts, "p", "pi", "PI Value Redefined !!!", ZPL_OPTS_FLOAT);
    zpl_opts_add(&opts, "4", "4pay", "hmmmm", ZPL_OPTS_INT);
    zpl_opts_add(&opts, "E", "enablegfx", "Enables HD resource pack", ZPL_OPTS_FLAG);

    zpl_opts_positional_add(&opts, "4pay");

    zpl_b32 ok=zpl_opts_compile(&opts, argc, argv);

    if (ok && zpl_opts_positionals_filled(&opts)) {

        zpl_b32 help=zpl_opts_has_arg(&opts, "help");
        if (help) {
            zpl_opts_print_help(&opts);
            return 0;
        }
        zpl_string foo=zpl_opts_string(&opts, "foo", "WRONG!");
        zpl_f64 some_num=zpl_opts_real(&opts, "pi", 0.0);
        zpl_i32 right=(zpl_i32)zpl_opts_integer(&opts, "4pay", 42);
        zpl_printf("The arg is %s\nPI value is: %f\nright: %d?\n", foo, some_num,
                   right);

        zpl_b32 gfx=zpl_opts_has_arg(&opts, "enablegfx");
        if (gfx) {
            zpl_printf("You wanted HD graphics? Here:\n\n");
            for (int i=0; i<5; ++i) {
                zpl_printf("iiiii\n");
            }
        }
    }
    else {
        zpl_opts_print_errors(&opts);
        zpl_opts_print_help(&opts);
    }

    return 0;
}
```

Have fun!

# Frequently Asked Questions

**What led you to the creation of this library?**

I personally found it rather cumbersome to re-implement commonly used features in C language. I used to use others' libraries to rely on those features. However, I once started extending those libraries by my own modules, breaking the style the original libraries were made. Thanks to FOSS, I've decided to fork [@gingerBill](https://github.com/gingerBill)'s library and adjusted it to my personal style and needs, while also returning bugfixes and some features back. ZPL later became independent and its own thing, adding new features,
code structure and QoL changes.

**Can I contribute to the project?**

Yes, indeed. This project is dual-licensed according to LICENSE, you are free to fork it, contribute to it or even sell it as you see fit.

**Why almost C99?**

Most parts of the library are written in pure C99. There are however, some additional components that require C11 to work (notably in the `Threading` module). As long as you are using minimal version (`ZPL_NANO`), and manually enable modules, the C99 support should be just fine.

**Why C99 though?**

Why not?

**Can I submit suggestions?**

Indeed, I'd also gladly discuss those with you on Discord, if possible.
