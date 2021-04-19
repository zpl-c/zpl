#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif

#define __PARSE(has_header) \
    zpl_csv_object r={0}; \
    zpl_u8 err = zpl_csv_parse(&r, (char *const)t, zpl_heap(), has_header);

#define __CLEANUP() \
    zpl_csv_free(&r);

MODULE(csv_parser, {
    IT("fails to parse empty data", {
        const char *t = "\n\n\n";
        __PARSE(false);

        EQUALS(err, ZPL_CSV_ERROR_UNEXPECTED_END_OF_INPUT);

        __CLEANUP();
    });

    IT("fails to parse mismatched csv rows", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo,bar,baz\n1,,2");
        __PARSE(true);

        EQUALS(err, ZPL_CSV_ERROR_MISMATCHED_ROWS);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses normal csv file", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo,bar,baz\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses single-column csv file", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo\n1\n2");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses single-row csv file", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo,1,2");
        __PARSE(false);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses single-value csv file", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo");
        __PARSE(false);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses csv file with quoted strings and escaped quotes", {
        SKIP();
        zpl_string t = zpl_string_make(zpl_heap(), "\"\"foo\"\"");
        __PARSE(false);

        EQUALS(err, 0);

        STREQUALS(r.nodes[0].nodes[0].string, "\"foo\"")

        __CLEANUP();
        zpl_string_free(t);
    });


    IT("parses csv file with quoted strings", {
        zpl_string t = zpl_string_make(zpl_heap(), "\"foo\",\"bar\",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses csv file with quoted strings containing commas", {
        zpl_string t = zpl_string_make(zpl_heap(), "\"foo, \",\"bar, \",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses csv file quoted strings containing newlines", {
        zpl_string t = zpl_string_make(zpl_heap(), "\"foo\nbaz\",\"bar\",\"baz\"\n1,2,3\n4,5,6\n");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses csv file with \"|\" delimiter", {
        zpl_string t = zpl_string_make(zpl_heap(), "foo|bar|baz\n1|2|3\n4|5|6\n");
        zpl_csv_object r={0};
        zpl_u8 err = zpl_csv_parse_delimiter(&r, (char *const)t, zpl_heap(), true, '|');

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses csv file with escaped quotes", {
        zpl_string t = zpl_string_make(zpl_heap(), "\" \"\"foo\"\" \",bar,baz\n1,2,3");
        __PARSE(true);

        EQUALS(err, 0);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("outputs valid csv data", {
        zpl_string original = zpl_string_make(zpl_heap(), "foo,bar,baz\n1,2,3\n");

        zpl_json_object doc, *foo, *bar, *baz;
        zpl_ast_set_obj(&doc, NULL, zpl_heap());
        {
            foo = zpl_ast_inset_arr(&doc, "foo");
            foo->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            {
                zpl_ast_node *n = zpl_ast_inset_str(foo, NULL, "1");
                n->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            }
            bar = zpl_ast_inset_arr(&doc, "bar");
            bar->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            {
                zpl_ast_node *n = zpl_ast_inset_str(bar, NULL, "2");
                n->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            }
            baz = zpl_ast_inset_arr(&doc, "baz");
            baz->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            {
                zpl_ast_node *n = zpl_ast_inset_str(baz, NULL, "3");
                n->name_style = ZPL_AST_NAME_STYLE_NO_QUOTES;
            }
        }
        zpl_string a = zpl_csv_write_string(zpl_heap(), &doc);
        STREQUALS(original, a);
        zpl_string_free(a);
        zpl_string_free(original);
    });
});

#undef __PARSE
#undef __CLEANUP
