#define __PARSE(has_header) \
    zpl_csv_object r={0}; \
    zpl_u8 err = zpl_csv_parse(&r, (char *const)t, mem_alloc, has_header);

MODULE(csv_parser, {
    IT("fails to parse empty data", {
        const char *t = "\n\n\n";
        __PARSE(false);

        EQUALS(err, ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT);
    });

    IT("fails to parse mismatched csv rows", {
        zpl_string t = zpl_string_make(mem_alloc, "foo,bar,baz\n1,2");
        __PARSE(true);

        EQUALS(err, ZPL_CSV_ERROR_MISMATCHED_ROWS);
    });

    IT("parses csv data with empty field in a row", {
        zpl_string t = zpl_string_make(mem_alloc, "foo,bar,baz\n1,,2");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses normal csv file", {
        zpl_string t = zpl_string_make(mem_alloc, "foo,bar,baz\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses single-column csv file", {
        zpl_string t = zpl_string_make(mem_alloc, "foo\n1\n2");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses single-row csv file", {
        zpl_string t = zpl_string_make(mem_alloc, "foo,1,2");
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes[0].nodes), 1);
        EQUALS(zpl_array_count(r.nodes[1].nodes), 1);
        EQUALS(zpl_array_count(r.nodes[2].nodes), 1);
    });

    IT("parses single-value csv file", {
        zpl_string t = zpl_string_make(mem_alloc, "foo");
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes[0].nodes), 1);
    });

    IT("parses csv file with quoted strings that contain escaped quotes", {
        zpl_string t = zpl_string_make(mem_alloc, "\" \"\"foo\"\" \"");
        __PARSE(false);

        EQUALS(err, 0);

        STREQUALS(r.nodes[0].nodes[0].string, " \"foo\" ")
    });


    IT("parses csv file with quoted strings", {
        zpl_string t = zpl_string_make(mem_alloc, "\"foo\",\"bar\",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses csv file with quoted strings containing commas", {
        zpl_string t = zpl_string_make(mem_alloc, "\"foo, \",\"bar, \",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses csv file quoted strings containing newlines", {
        zpl_string t = zpl_string_make(mem_alloc, "\"foo\nbaz\",\"bar\",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("parses csv file with \"|\" delimiter", {
        zpl_string t = zpl_string_make(mem_alloc, "foo|bar|baz\n1|2|3\n4|5|6\n");
        zpl_csv_object r={0};
        zpl_u8 err = zpl_csv_parse_delimiter(&r, (char *const)t, mem_alloc, true, '|');

        EQUALS(err, 0);
    });

    IT("parses csv file with escaped quotes", {
        zpl_string t = zpl_string_make(mem_alloc, "\" \"\"foo\"\" \",bar,baz\n1,2,3");
        __PARSE(true);

        EQUALS(err, 0);
    });

    IT("outputs valid csv data", {
        zpl_string original = zpl_string_make(mem_alloc, "foo,bar,baz\n1,2,3\n");

        zpl_json_object doc, *foo, *bar, *baz;
        zpl_adt_set_obj(&doc, NULL, mem_alloc);
        {
            foo = zpl_adt_append_arr(&doc, "foo");
            foo->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(foo, NULL, "1");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
            bar = zpl_adt_append_arr(&doc, "bar");
            bar->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(bar, NULL, "2");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
            baz = zpl_adt_append_arr(&doc, "baz");
            baz->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(baz, NULL, "3");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
        }
        zpl_string a = zpl_csv_write_string(mem_alloc, &doc);
        STREQUALS(original, a);
    });

    IT("outputs valid csv data with one empty field", {
        zpl_string original = zpl_string_make(mem_alloc, "foo,bar,baz\n1,,3\n");

        zpl_json_object doc, *foo, *bar, *baz;
        zpl_adt_set_obj(&doc, NULL, mem_alloc);
        {
            foo = zpl_adt_append_arr(&doc, "foo");
            foo->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(foo, NULL, "1");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
            bar = zpl_adt_append_arr(&doc, "bar");
            bar->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(bar, NULL, "");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
            baz = zpl_adt_append_arr(&doc, "baz");
            baz->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(baz, NULL, "3");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
        }
        zpl_string a = zpl_csv_write_string(mem_alloc, &doc);
        STREQUALS(original, a);
    });

    IT("outputs valid csv data with one empty quoted field", {
        zpl_string original = zpl_string_make(mem_alloc, "foo,bar,baz\n1,\"\",3\n");

        zpl_json_object doc, *foo, *bar, *baz;
        zpl_adt_set_obj(&doc, NULL, mem_alloc);
        {
            foo = zpl_adt_append_arr(&doc, "foo");
            foo->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(foo, NULL, "1");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
            bar = zpl_adt_append_arr(&doc, "bar");
            bar->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(bar, NULL, "");
                n->name_style = ZPL_ADT_NAME_STYLE_DOUBLE_QUOTE;
            }
            baz = zpl_adt_append_arr(&doc, "baz");
            baz->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            {
                zpl_adt_node *n = zpl_adt_append_str(baz, NULL, "3");
                n->name_style = ZPL_ADT_NAME_STYLE_NO_QUOTES;
            }
        }
        zpl_string a = zpl_csv_write_string(mem_alloc, &doc);
        STREQUALS(original, a);
    });

    IT("outputs valid csv data with escaped double quotes", {
        zpl_string original = zpl_string_make(mem_alloc, "\"x \"\"test\"\" x\"\n");

        zpl_json_object doc, *node;
        zpl_adt_set_arr(&doc, NULL, mem_alloc);
        {
            node = zpl_adt_append_arr(&doc, NULL);
            {
                zpl_adt_node *n = zpl_adt_append_str(node, NULL, "x \"test\" x");
                n->name_style = ZPL_ADT_NAME_STYLE_DOUBLE_QUOTE;
            }
        }
        zpl_string a = zpl_csv_write_string(mem_alloc, &doc);
        STREQUALS(original, a);
    });

    IT("parses csv file with unquoted IP addresses", {
        zpl_string t = zpl_string_make(mem_alloc, "\"foo\",123.45.67.89\n");
        __PARSE(true);

        EQUALS(err, 0);
        EQUALS(r.nodes[1].nodes[0].type, ZPL_ADT_TYPE_STRING);
        STREQUALS(r.nodes[1].nodes[0].string, "123.45.67.89");
    });

    IT("parses 'x' field as string", {
        zpl_string t = zpl_string_make(mem_alloc, "x\n");
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(r.nodes[0].nodes[0].type, ZPL_ADT_TYPE_STRING);
        STREQUALS(r.nodes[0].nodes[0].string, "x");
    });

    IT("parses 'n' field as string", {
        zpl_string t = zpl_string_make(mem_alloc, "n\n");
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(r.nodes[0].nodes[0].type, ZPL_ADT_TYPE_STRING);
        STREQUALS(r.nodes[0].nodes[0].string, "n");
    });
});

#undef __PARSE
