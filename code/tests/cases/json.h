#define __PARSE() \
    zpl_json_object r={0}; \
    zpl_u8 err = zpl_json_parse(&r, (char *)t, mem_alloc);

MODULE(json5_parser, {
    IT("parses empty JSON5 object", {
        const char *t = "{}";
        __PARSE();

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.type, ZPL_ADT_TYPE_OBJECT);
    });

    IT("parses empty JSON5 array", {
        const char *t = "  [    ]";
        __PARSE();

        EQUALS(err, 0);
        EQUALS(r.type, ZPL_ADT_TYPE_ARRAY);
    });

    IT("parses cfg mode document", {
        zpl_string t = zpl_string_make(mem_alloc, "\n\nfoo = \"bar\"\nbaz = 123\n\n");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(r.type, ZPL_ADT_TYPE_OBJECT);
    });

    IT("can produce a compact JSON output", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                {
                    "foo": "bar",
                    "baz": 123
                }));
        __PARSE();

        EQUALS(err, 0);
        EQUALS(r.type, ZPL_ADT_TYPE_OBJECT);

        zpl_string out = zpl_json_write_string(mem_alloc, &r, ZPL_JSON_INDENT_STYLE_COMPACT);
        STREQUALS(out, "{\"foo\":\"bar\",\"baz\":123}");
    });

    IT("can produce a valid, compact SJSON output", {
        zpl_string t = zpl_string_make(mem_alloc, "foo=\"bar\",baz=123");
        __PARSE();

        EQUALS(err, 0);
        EQUALS(r.type, ZPL_ADT_TYPE_OBJECT);

        zpl_string out = zpl_json_write_string(mem_alloc, &r, ZPL_JSON_INDENT_STYLE_COMPACT);
        STREQUALS(out, "foo=\"bar\",baz=123");
    });

    IT("fails to parse broken JSON5 array", {
        const char *t = "[   }";
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_ARRAY_LEFT_OPEN);
    });

    IT("fails to parse broken JSON5 object", {
        const char *t = "{ \t]";
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_OBJECT_END_PAIR_MISMATCHED);
    });

    IT("fails to parse invalid data", {
        const char *t = "{{jsdljsdksd{}}{]][{}";
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_UNKNOWN_KEYWORD);
    });

    IT("parses commented JSON5 object", {
        zpl_string t = zpl_string_make(mem_alloc, "{/* TEST CODE */ \"a\": 123 }");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.nodes[0].type, ZPL_ADT_TYPE_INTEGER);
        EQUALS(r.nodes[0].integer, 123);
    });

    IT("parses commented JSON5 array", {
        zpl_string t = zpl_string_make(mem_alloc, "[/* TEST CODE */ 123 ]");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.nodes[0].type, ZPL_ADT_TYPE_INTEGER);
        EQUALS(r.nodes[0].integer, 123);
    });

    IT("parses JSON array of multiple values", {
        zpl_string t = zpl_string_make(mem_alloc, "[ 123, 456, `hello` ]");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 3);
        EQUALS(r.nodes[0].integer, 123);
        EQUALS(r.nodes[1].integer, 456);
        STREQUALS(r.nodes[2].string, "hello");
    });

    IT("parses commented JSON5 document", {
        zpl_string t = zpl_string_make(mem_alloc, ""
                "{\n"
                    "$api: \"opengl\",\n"
                    "name: \"Diffuse shader\",\n"
                    "version: \"150\",\n"
                    "type: \"fragment\",\n"
                    "// These are shader uniforms\n"
                    "uniforms: [\n"
                        "{ name: 'l_pos', type: 'vec3'},\n"
                        "{ name: 'l_mat', type: 'mat4'},\n"
                    "],\n"
                    "_meta: \"0 0 -34 2.34 123 2.34e-4\",\n"
                    "/* GLSL shader code */\n"
                    "code: `\n"
                        "uniform vec3 l_pos;\n"
                        "uniform mat4 l_mat;\n"
                        "void main() {\n"
                            "// ...\n"
                        "}\n"
                    "`,\n"
                "}\n");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 7);
    });

    IT("parses nested array", {
        const char *t = ZPL_MULTILINE(\
                [
                    [
                        [
                        ]
                    ]
                ]);
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
    });

    IT("parses nested array inside of an object", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                { "foo": [
                    [
                        [
                        ]
                    ]
                ]}));
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
    });

    IT("parses keywords", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                [
                    true,
                    false,
                    null,
                    Infinity,
                    -Infinity,
                    NaN,
                    -NaN
                ]));
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
    });

    IT("parses empty object as a field", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                {
                    "foo": {}
                }));
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
    });

    IT("parses numbers with scientific notation", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                {
                    "foo": 1.e-2,
                    "bar": 42.23e4,
                    "baz": .032,
                    "bag": -232412.00349792
                }));
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(r.nodes[0].base, 1);
        EQUALS(r.nodes[0].exp, -2);

        EQUALS(r.nodes[1].base, 42);
        EQUALS(r.nodes[1].base2, 23);
        EQUALS(r.nodes[1].base2_offset, 0);
        EQUALS(r.nodes[1].exp, 4);

        EQUALS(r.nodes[2].base2, 32);
        EQUALS(r.nodes[2].base2_offset, 1);
        EQUALS(r.nodes[2].lead_digit, false);

        EQUALS(r.nodes[3].base, -232412);
        EQUALS(r.nodes[3].base2, 349792);
        EQUALS(r.nodes[3].base2_offset, 2);
    });

    IT("parses minified JSON array", {
        zpl_string t = zpl_string_make(mem_alloc, "[{\"Name\":\"ATLAS0.png\",\"Width\":256,\"Height\":128,\"Images\":[{\"Name\":\"4\",\"X\":0,\"Y\":0,\"Width\":40,\"Height\":27,\"FrameX\":0,\"FrameY\":0,\"FrameW\":40,\"FrameH\":27},{\"Name\":\"0\",\"X\":41,\"Y\":0,\"Width\":40,\"Height\":27,\"FrameX\":0,\"FrameY\":0,\"FrameW\":40,\"FrameH\":27},{\"Name\":\"6\",\"X\":82,\"Y\":0,\"Width\":33,\"Height\":35,\"FrameX\":0,\"FrameY\":0,\"FrameW\":33,\"FrameH\":35},{\"Name\":\"2\",\"X\":0,\"Y\":28,\"Width\":33,\"Height\":35,\"FrameX\":0,\"FrameY\":0,\"FrameW\":33,\"FrameH\":35},{\"Name\":\"7\",\"X\":36,\"Y\":28,\"Width\":31,\"Height\":38,\"FrameX\":0,\"FrameY\":0,\"FrameW\":31,\"FrameH\":38},{\"Name\":\"3\",\"X\":118,\"Y\":0,\"Width\":31,\"Height\":38,\"FrameX\":0,\"FrameY\":0,\"FrameW\":31,\"FrameH\":38},{\"Name\":\"5\",\"X\":157,\"Y\":0,\"Width\":37,\"Height\":34,\"FrameX\":0,\"FrameY\":0,\"FrameW\":37,\"FrameH\":34},{\"Name\":\"1\",\"X\":118,\"Y\":32,\"Width\":37,\"Height\":34,\"FrameX\":0,\"FrameY\":0,\"FrameW\":37,\"FrameH\":34}],\"IsRotated\":true,\"IsTrimmed\":false,\"IsPremultiplied\":false}]");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 1);
        EQUALS(zpl_array_count(r.nodes[0].nodes), 7);
        EQUALS(r.nodes[0].nodes[3].type, ZPL_ADT_TYPE_ARRAY);
        EQUALS(zpl_array_count(r.nodes[0].nodes[3].nodes), 8);
    });

    IT("parses geojson.io data", {
        zpl_string t = zpl_string_make(mem_alloc, "{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[19.09149169921875,48.55786390423251],[19.172515869140625,48.55786390423251],[19.172515869140625,48.60101970261553],[19.09149169921875,48.60101970261553],[19.09149169921875,48.55786390423251]]]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"LineString\",\"coordinates\":[[19.149169921875,48.56024979174329],[16.63330078125,49.160154652338015],[18.28125,49.82380908513249],[18.720703125,49.210420445650286],[19.62158203125,48.929717630629554],[19.13818359375,48.58205840283824]]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Point\",\"coordinates\":[17.962646484375,48.17341248658084]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[18.4130859375,47.68388118858139],[19.951171875,47.00647991252098],[20.819091796874996,47.83159592699297],[19.237060546875,48.19904897935913],[18.380126953125,48.06706753191901],[17.633056640625,47.67648444221321],[17.764892578124996,47.21583707523794],[18.4130859375,47.68388118858139]]]}}]}");
        __PARSE();

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);
    });

    IT("writes a complex JSON5 document", {
        zpl_string original = zpl_string_make(mem_alloc, ""
                "{\n"
                "    \"$api\": \"opengl\",\n"
                "    \"name\": \"Diffuse shader\",\n"
                "    \"version\": 150,\n"
                "    \"type\": \"fragment\",\n"
                "    \"uniforms\": [{\n"
                "        \"name\": \"l_pos\",\n"
                "        \"type\": \"vec3\"\n"
                "    }, {\n"
                "        \"name\": \"l_mat\",\n"
                "        \"type\": \"mat4\"\n"
                "    }],\n"
                "    \"_meta\": \"0 0 -34 2.34 123 2.34e-4\"\n"
                "}\n"
        );

        zpl_json_object doc, *o, *o2;
        zpl_adt_set_obj(&doc, NULL, mem_alloc);

        o = zpl_adt_append_str(&doc, "$api", "opengl");
        o = zpl_adt_append_str(&doc, "name", "Diffuse shader");
        o = zpl_adt_append_int(&doc, "version", 150);
        o = zpl_adt_append_str(&doc, "type", "fragment");
        o = zpl_adt_append_arr(&doc, "uniforms");
        {
            o2 = zpl_adt_append_obj(o, NULL);
            {
                zpl_adt_append_str(o2, "name", "l_pos");
                zpl_adt_append_str(o2, "type", "vec3");
            }
            o2 = zpl_adt_append_obj(o, NULL);
            {
                zpl_adt_append_str(o2, "name", "l_mat");
                zpl_adt_append_str(o2, "type", "mat4");
            }
        }
        o = zpl_adt_append_str(&doc, "_meta", "0 0 -34 2.34 123 2.34e-4");

        zpl_string a = zpl_json_write_string(mem_alloc, &doc, 0);
        STREQUALS(original, a);
    });

    IT("handles out of memory during parse", {
        zpl_string t = zpl_string_make(mem_alloc, ZPL_MULTILINE(\
                {
                    "test1": "test",
                    "test2": 123,
                    "test3": {
                        "test3.1": 456
                    },
                    "test4": [ 789 ],
                    "test5": true,
                    "test6": false,
                    "test7": Infinity,
                    "test8": -Infinity,
                    "test9": NaN,
                    "test10": -NaN
                }));
		char *buffer = zpl_malloc(1);
        for (int i = 1; true; i++) {
			buffer = zpl_resize(zpl_heap(), buffer, i-1, i);
            zpl_arena arena;
            zpl_arena_init_from_memory(&arena, buffer, i);
            zpl_allocator allocator = zpl_arena_allocator(&arena);

            zpl_json_object r={0};
            zpl_u8 err = zpl_json_parse(&r, (char *)t, allocator);
			if (err == ZPL_JSON_ERROR_OUT_OF_MEMORY)
				continue;
            EQUALS(err, ZPL_JSON_ERROR_NONE);
            EQUALS(zpl_array_count(r.nodes), 10);
            break;
        }
		zpl_mfree(buffer);
    });

    IT("handles out of memory during construction", {
       char *buffer = zpl_malloc(1);
	   for (int i = 1; true; i++) {
		    buffer = zpl_resize(zpl_heap(), buffer, i-1, i);
            zpl_arena arena;
            zpl_arena_init_from_memory(&arena, buffer, i);
            zpl_allocator allocator = zpl_arena_allocator(&arena);

            zpl_json_object doc, *o, *o2;
            if (zpl_adt_set_obj(&doc, NULL, allocator) == ZPL_ADT_ERROR_OUT_OF_MEMORY) continue;

            o = zpl_adt_append_str(&doc, "test1", "test");
            if (!o) continue;
            o = zpl_adt_append_int(&doc, "test2", 123);
            if (!o) continue;
            o = zpl_adt_append_obj(&doc, "test3");
            if (!o) continue;
            {
                o2 = zpl_adt_append_int(o, "test3.1", 456);
                if (!o2) continue;
            }
            o = zpl_adt_append_arr(&doc, "test4");
            if (!o) continue;
            {
                o2 = zpl_adt_append_int(o, NULL, 789);
                if (!o2) continue;
            }
            o = zpl_adt_append_flt(&doc, "test5", 1);
            if (!o) continue;
            o = zpl_adt_append_flt(&doc, "test6", 0);
            if (!o) continue;
            o = zpl_adt_append_str(&doc, "test7", "foo");
            if (!o) continue;
            o = zpl_adt_append_str(&doc, "test8", "bar");
            if (!o) continue;
            o = zpl_adt_append_str(&doc, "test9", "test");
            if (!o) continue;

            zpl_string a = zpl_json_write_string(allocator, &doc, 0);
            if (!a) continue;

            zpl_string expected = zpl_string_make(mem_alloc, ""
                    "{\n"
                    "    \"test1\": \"test\",\n"
                    "    \"test2\": 123,\n"
                    "    \"test3\": {\n"
                    "        \"test3.1\": 456\n"
                    "    },\n"
                    "    \"test4\": [789],\n"
                    "    \"test5\": 1.000000,\n"
                    "    \"test6\": 0,\n"
                    "    \"test7\": \"foo\",\n"
                    "    \"test8\": \"bar\",\n"
                    "    \"test9\": \"test\"\n"
                    "}\n"
            );
            STREQUALS(expected, a);
            break;
        }
	    zpl_mfree(buffer);
	});
});

#undef __PARSE
