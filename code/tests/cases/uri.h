#define __PARSE() \
    zpl_uri_object r={0}; \
    zpl_u8 err = zpl_uri_parse(&r, (char *const)t, mem_alloc);

MODULE(uri_parser, {
    IT("parses an empty uri string", {
        zpl_string t = zpl_string_make(mem_alloc, "");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 0);
    });

    IT("parses normal uri string", {
        zpl_string t = zpl_string_make(mem_alloc, "https://example.com?foo=bar&baz=qux");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 3);
    });

    IT("parses uri string without origin address", {
        zpl_string t = zpl_string_make(mem_alloc, "?foo=bar&baz=qux");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 2);
    });

    IT("parses uri string with encoded '+' spaces", {
        zpl_string t = zpl_string_make(mem_alloc, "?foo=bar+baz");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 1);
    });

    IT("parses uri string with encoded '%20' spaces", {
        zpl_string t = zpl_string_make(mem_alloc, "?foo=bar%20baz");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 1);
    });

    IT("parses uri string with special characters", {
        zpl_string t = zpl_string_make(mem_alloc, "https://example.com/dir1/page2?param1=%C5%BDe+pre%C4%8Do+sa+to+deje%3F&param2=10&enable_cookies&param3=test%28floor%29&symbols=%21+%2A+%27+%28+%29+%3B+%3A+%40+%26+%3D+%2B+%24+%2C+%2F+%3F+%25+%23+%5B+%5D");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 6);
    });

    IT("parses uri string and decodes params properly", {
        zpl_string t = zpl_string_make(mem_alloc, "https://example.com/dir1/page2?param1=%C5%BDe+pre%C4%8Do+sa+to+deje%3F&param2=10&enable_cookies&param3=test%28floor%29&symbols=%21+%2A+%27+%28+%29+%3B+%3A+%40+%26+%3D+%2B+%24+%2C+%2F+%3F+%25+%23+%5B+%5D");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 6);
        STREQUALS(zpl_adt_query(&r, "param1")->string, "Že prečo sa to deje?");   
        STREQUALS(zpl_adt_query(&r, "symbols")->string, "! * ' ( ) ; : @ & = + $ , / ? % # [ ]");
    });

    IT("generates valid URI payload from ADT node", {
        zpl_uri_object custom = {0};
        zpl_uri_init(&custom, NULL, mem_alloc);
        zpl_adt_append_str(&custom, "foo", "bar");
        zpl_adt_append_str(&custom, "param1", "Že prečo sa to deje?");
        zpl_adt_node *cookies = zpl_adt_append_flt(&custom, "enable_cookies", 1);
        cookies->props = ZPL_ADT_PROPS_TRUE;
        zpl_string out = zpl_uri_write_string(mem_alloc, &custom);
        STREQUALS(out, "?foo=bar&param1=%C5%BDe+pre%C4%8Do+sa+to+deje%3F&enable_cookies");
    });

    IT("generates valid URI payload with empty ADT string node", {
        zpl_uri_object custom = {0};
        zpl_uri_init(&custom, NULL, mem_alloc);
        zpl_adt_append_str(&custom, "foo", "");
        zpl_adt_append_str(&custom, "param1", NULL);
        zpl_string out = zpl_uri_write_string(mem_alloc, &custom);
        STREQUALS(out, "?foo=&param1=");
    });

    IT("parses URI payload with empty ADT string node", {
        zpl_string t = zpl_string_make(mem_alloc, "?foo=&bar=");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 2);
    });

    IT("parses URI payload with ? used as param delimiter", {
        zpl_string t = zpl_string_make(mem_alloc, "?foo=1?bar=2?baz=3");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 3);
    });
});

#undef __PARSE
