#define RUN(desc, exp, fmt, ...) \
    IT(desc, { \
        const char *txt = zpl_bprintf(fmt, __VA_ARGS__); \
        STREQUALS(exp, txt); \
    });

MODULE(print, {
    RUN("can print formatted text", "hello world! number: 42\n", "hello %s! number: %d\n", "world", 42);
    RUN("can print fixed-size string", "conven", "%.6s", "convenience");
    RUN("can print variable-sized string", "conven", "%.*s", 6, "convenience");
    RUN("can print float with fixed precision", "5.42", "%.2f", 5.423559);
    RUN("can print float with variable-width precision", "5.423", "%.*f", 3, 5.423559);
    RUN("can print a number with padded zeroes", "2.500", "%.3f", 2.5);
    RUN("can print octal numbers", "0666", "0%o", 0666);
    RUN("can print hexadecimal numbers", "0xDEADBEEF", "0x%X", 0xDEADBEEF);
    RUN("can print hexadecimal numbers (lowercase)", "0xdeadbeef", "0x%x", 0xdeadbeef);
    RUN("can print table data", "* worker 1  hits: 1234     idle: 34 cy.", "* worker %-2u hits: %-8d idle: %d cy.", 1, 1234, 34);
    RUN("can pad text out with arbitrary symbol and width", "==== hello", "%4r hello", '=');

    IT("can allocate formatted string", {
        char *test;
        zpl_isize res;
        res = zpl_asprintf(zpl_heap(), &test, "hello %s", "world");
        EQUALS(12, res);
        STREQUALS(test, "hello world");
        zpl_mfree(test);
    });

    IT("can print hexadecimal floating-point value", {
        SKIP();
    });
});

#undef RUN
