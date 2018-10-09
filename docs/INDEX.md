# Introduction
It's been created to simplify development process under C/C++ language and offers commonly used set of features that C developers often re-invent or search libraries for. Apart from helper methods that replace/extend C standard library, this toolkit also consists of modules that are very helpful in specific areas of expertise, such as graph culling algorithms, JSON5 parser, OpenGL-friendly math library as well as OpenGL helper module and many more...

Library is cross-platform and currently works on **i386**, **amd64** and **ARM** architectures. It has been tested on **Windows**, **UNIX systems**, **iOS**, **Emscripten** and **Android**.

## Honorable users of this library

* [librg](https://github.com/librg/librg) - Pure C99 game networking library for building simple and elegant cross-platform client-server solutions.

# Table of Contents
ZPL consists of the following modules:
* **Macro helpers** - This module contains many useful macros helpful for debugging as well as development itself.
* **Memory** - Consists of pointer arithmetic methods, virtual memory management and custom memory allocators.
* **Threading** - This module features common threading and blocking principles. It contains thread merge operation based on stb_sync, as well as CPU affinity management.
* **Sorting** - Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains simple implementation of binary search, as well as an easy to use API to define your own comparators.
* **String** - Offers methods for c-string manipulation, but also a string library based on gb_string, which is c-string friendly.
* **Regex** - Port of gb_regex with several bugfixes applied. This is a simple regex library and is fast to perform.
* **Containers** - Consists of C++ template-like macros that define containers for any type. All of these containers are C friendly and accessible using `de-reference` or `[]` operators. These are: buffer, array, linked-list, ring buffer.
* **Hashing** - Several hashing methods used by ZPL internally but possibly useful outside of it. Contains: adler32, crc32/64, fnv32/64/a and murmur32/64
* **Hashtable** - An instantiated hashtable implementation which works for any type defined.
* **File** - File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.
* **Print** - Re-implementation of printf methods.
* **DLL** - Helper methods for loading a dynamic library. It also offers an ability to load a procedure address.
* **Time** - Helper methods for retrieving the current time in many forms under different precisions. It also offers a simple to use timer library.
* **Event** - Simple event handler which can fire multiple callbacks per registered event.
* **JSON5 parser** - Easy to use and very fast JSON5 parser that can easily load 50 megabytes of JSON content under half a second. It also contains simple JSON5 writer and acts as a good library for handling config files.
* **Opts** - Opts is a CLI options parser, it can parse flags, switches and arguments from command line and offers an easy way to express input errors as well as the ability to display help screen.
* **Thread pool** - Can set up a batch of workers which use thread-pool pattern to handle async tasks without the unecessary threading overhead.
* **Math** - OpenGL gamedev friendly library for math.
* **Platform layer** - A port of gb_platform which gains access to window and input management, as well as graphics. (Works only on Windows so far).
* **Miscellaneous** - Methods that don't belong anywhere but are still very useful in many occasions.

## External modules
These are modules that work either as a standalone library or didn't fit into the ZPL library itself:
* **zpl_opengl.h** - Offers OpenGL helper methods as well as basic 2D sprite and font rendering.
* **zpl_glgen.py** - A Python script which fetches `glcorearb.h` to generate `zpl_glgen.h` which acts as an OpenGL extension wrangler.
* **zpl_image.h** - Image manipulation methods and simple GIF reading API.
* **zpl_cull.h** - Graph 2D/3D culling library.

This repository also contains third-party libraries which were either included or modified to be used by some of these ZPL external modules.

## Documentation
Documentation is available in its generated form at [zpl.readthedocs.io](https://zpl.rtfd.io/).

You can see all modules by accessing the left panel's **Modules** link by accessing **Files** > **File List** to see all files instead.

Note that the documentation is still work in progress and will be tweaked further.

You can build the documentation using Doxygen 1.8.11 or later. We use Sphinx to build ReadTheDocs.io friendly documentation, which uses Doxygen to generate it.

# Example Usage
In this example, I'll show you how to write a simple JSON5 benchmark tool by using ZPL only.

First, I recommend looking at zpl.h header file, which describes how to use the library. Now you know, that to use zpl.h in your project, you have to define `ZPL_IMPLEMENTATION` exactly in **ONE SOURCE** file **BEFORE** including the zpl.h file itself to successfully embed it.

Afterwards, we need to deal with file loading, this time, we can either search for file module inside of zpl.h (not recommended), or we can navigate to `code/zpl/` to see the original form of the ZPL library. 

As you can see, each module is contained within its own source file. There's also a Python script called `build.py` which generates a new zpl.h file, combining all these modules together. 

Here we need `_file.c`, which contains necessary file i/o operations. Write a code to read `test.json5` file (you can use zpl_file_read_contents) and try to print its content (either use libc's printf or methods from `_print.c`) Check test folder for code examples.

Done? Great! Now we need to parse this file, but how? Well guess what, `_json.c` is exactly what you're looking for! Now you might wonder, you can parse JSON5 files...

But what use is it for a benchmark tool if it doesn't even let you know how long the process took? It is time (pun intended) to visit `_time.c` file now, capture 2 timestamps, one before, another after the operation and the difference is your time you can display to user. Or just check out code examples in test folder.

What's left? We can read a specific JSON5 file, parse it and display the time it took to do so. Did I say.. specific? How about we let the user customise the options on the command line? 

Visit `_opts.c` and get to know it. As always, test folder can be useful in this case. 

Actually, the following snippet comes from the `json_benchmark.c` test file:

```c
#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main(int argc, char **argv) {
    zpl_opts opts={0};

    zpl_opts_init(&opts, zpl_heap(), argv[0]);

    zpl_opts_add(&opts, "f", "file", "input file name.", ZPL_OPTS_STRING);
    zpl_opts_add(&opts, "s", "strip-comments", "strip comments from JSON file (recommended).", ZPL_OPTS_FLAG);

    zpl_opts_positional_add(&opts, "file");

    b32 ok = zpl_opts_compile(&opts, argc, argv);

    char *filename = NULL;
    b32 strip_comments = false;

    if (ok && zpl_opts_positionals_filled(&opts))
    {
        filename = zpl_opts_string(&opts, "file", NULL);
        strip_comments = zpl_opts_has_arg(&opts, "strip-comments");

        if (filename == NULL)
            goto bad;

        printf("Filename: %s\n", filename);
    }
    else
    {
        bad:
        zpl_opts_print_errors(&opts);
        zpl_opts_print_help(&opts);
        return -1;
    }

    zpl_file_contents fc = zpl_file_read_contents(zpl_heap(), true, filename);

    printf("Parsing JSON5 file!\n");

    zpl_json_object root = {0};

    u8 err;
    f64 time = zpl_time_now();
    zpl_json_parse(&root, fc.size, (char *)fc.data, zpl_heap(), strip_comments, &err);
    f64 delta = zpl_time_now() - time;

    if (err == ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL)
    {
        printf("File not found!\n");
        return -2;
    }

    printf("Delta: %fms\nNo. of nodes: %lld\nError code: %d\nFile size: %lld bytes\n", delta*1000, zpl_array_count(root.nodes), err, fc.size);

    zpl_json_free(&root);
    zpl_file_free_contents(&fc);
    
    return 0;
}
```

Have fun!


# Frequently Asked Questions

**What led you to the creation of this library?**

I personally found it rather cumbersome to re-implement commonly used features in C language. I used to use others' libraries to rely on those features. However, I once started extending those libraries by my own modules, breaking the style the original libraries were made. Thanks to FOSS, I've decided to fork @gingerBill's library and adjusted it to my personal style and needs, while also returning bugfixes and some features back. ZPL later became independent and its own thing.

**Can I contribute to the project?**

Yes, indeed. This project is dual-licensed according to LICENSE, you are free to fork it, contribute to it or even sell it as you see fit.

**Why C99?**

Why not?

**Can I submit suggestions?**

Indeed, I'd also gladly discuss those with you on Discord, if possible.
 
