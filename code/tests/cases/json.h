#ifdef ZPL_EDITOR
    #include <zpl.h>
    #include "unit.h"
#endif

#define __PARSE(comments) \
    zpl_json_object r={0}; \
    zpl_json_parse(&r, (char *const)t, zpl_heap(), &err);

#define __CLEANUP() \
    zpl_json_free(&r);

MODULE(json5_parser, {
    zpl_u8 err = 0;
    IT("parses empty JSON5 object", {
        const char *t = "{}";
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.type, ZPL_AST_TYPE_OBJECT);

        __CLEANUP();
    });

    IT("parses empty JSON5 array", {
        const char *t = "  [    ]";
        __PARSE(false);

        EQUALS(err, 0);
        EQUALS(r.type, ZPL_AST_TYPE_ARRAY);

        __CLEANUP();
    });

    IT("fails to parse broken JSON5 array", {
        const char *t = "[   }";
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_INVALID_VALUE);

        __CLEANUP();
    });

    IT("fails to parse broken JSON5 object", {
        const char *t = "{ \t]";
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_INVALID_VALUE);

        __CLEANUP();
    });

    IT("fails to parse invalid data", {
        const char *t = "{{jsdljsdksd{}}{]][{}";
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_INVALID_VALUE);

        __CLEANUP();
    });

    IT("parses commented JSON5 object", {
        zpl_string t = zpl_string_make(zpl_heap(), "{/* TEST CODE */ \"a\": 123 }");
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.nodes[0].type, ZPL_AST_TYPE_INTEGER);
        EQUALS(r.nodes[0].integer, 123);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses commented JSON5 array", {
        zpl_string t = zpl_string_make(zpl_heap(), "[/* TEST CODE */ 123 ]");
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);
        EQUALS(r.nodes[0].type, ZPL_AST_TYPE_INTEGER);
        EQUALS(r.nodes[0].integer, 123);

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses JSON array of multiple values", {
        zpl_string t = zpl_string_make(zpl_heap(), "[ 123, 456, `hello` ]");
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 3);
        EQUALS(r.nodes[0].integer, 123);
        EQUALS(r.nodes[1].integer, 456);
        STREQUALS(r.nodes[2].string, "hello");

        __CLEANUP();
        zpl_string_free(t);
    });

    IT("parses commented JSON5 document", {
        zpl_string t = zpl_string_make(zpl_heap(), ZPL_MULTILINE(\
                {
                    $api: "opengl",
                    name: "Diffuse shader",
                    version: "150",
                    type: "fragment",
                    // These are shader uniforms
                    uniforms: [
                        { name: 'l_pos', type: 'vec3'},
                        { name: 'l_mat', type: 'mat4'},
                    ],
                    _meta: "0 0 -34 2.34 123 2.34e-4",

                    /* GLSL shader code */
                    code: `
                        uniform vec3 l_pos;
                        uniform mat4 l_mat;

                        void main() {
                            // ...
                        }
                    `,
                }));
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 7);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("parses nested array", {
        const char *t = ZPL_MULTILINE(\
                [
                    [
                        [
                        ]
                    ]
                ]);
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);

        __CLEANUP();
    });

    IT("parses nested array inside of an object", {
        zpl_string t = zpl_string_make(zpl_heap(), ZPL_MULTILINE(\
                { "foo": [
                    [
                        [
                        ]
                    ]
                ]}));
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("parses keywords", {
        zpl_string t = zpl_string_make(zpl_heap(), ZPL_MULTILINE(\
                [
                    true,
                    false,
                    null,
                    Infinity,
                    -Infinity,
                    NaN,
                    -NaN
                ]));
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("parses empty object as a field", {
        zpl_string t = zpl_string_make(zpl_heap(), ZPL_MULTILINE(\
                {
                    "foo": {}
                }));
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("parses numbers with scientific notation", {
        zpl_string t = zpl_string_make(zpl_heap(), ZPL_MULTILINE(\
                {
                    "foo": 1.e-2,
                    "bar": 42.23e4,
                    "baz": .032
                }));
        __PARSE(true);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(r.nodes[0].base, 1);
        EQUALS(r.nodes[0].exp, 2);
        EQUALS(r.nodes[0].exp_neg, true);

        EQUALS(r.nodes[1].base, 42);
        EQUALS(r.nodes[1].base2, 23);
        EQUALS(r.nodes[1].base2_offset, 0);
        EQUALS(r.nodes[1].exp, 4);

        EQUALS(r.nodes[2].base2, 32);
        EQUALS(r.nodes[2].base2_offset, 1);
        EQUALS(r.nodes[2].lead_digit, false);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("parses minified JSON array", {
        zpl_string t = zpl_string_make(zpl_heap(), "[{\"Name\":\"ATLAS0.png\",\"Width\":256,\"Height\":128,\"Images\":[{\"Name\":\"4\",\"X\":0,\"Y\":0,\"Width\":40,\"Height\":27,\"FrameX\":0,\"FrameY\":0,\"FrameW\":40,\"FrameH\":27},{\"Name\":\"0\",\"X\":41,\"Y\":0,\"Width\":40,\"Height\":27,\"FrameX\":0,\"FrameY\":0,\"FrameW\":40,\"FrameH\":27},{\"Name\":\"6\",\"X\":82,\"Y\":0,\"Width\":33,\"Height\":35,\"FrameX\":0,\"FrameY\":0,\"FrameW\":33,\"FrameH\":35},{\"Name\":\"2\",\"X\":0,\"Y\":28,\"Width\":33,\"Height\":35,\"FrameX\":0,\"FrameY\":0,\"FrameW\":33,\"FrameH\":35},{\"Name\":\"7\",\"X\":36,\"Y\":28,\"Width\":31,\"Height\":38,\"FrameX\":0,\"FrameY\":0,\"FrameW\":31,\"FrameH\":38},{\"Name\":\"3\",\"X\":118,\"Y\":0,\"Width\":31,\"Height\":38,\"FrameX\":0,\"FrameY\":0,\"FrameW\":31,\"FrameH\":38},{\"Name\":\"5\",\"X\":157,\"Y\":0,\"Width\":37,\"Height\":34,\"FrameX\":0,\"FrameY\":0,\"FrameW\":37,\"FrameH\":34},{\"Name\":\"1\",\"X\":118,\"Y\":32,\"Width\":37,\"Height\":34,\"FrameX\":0,\"FrameY\":0,\"FrameW\":37,\"FrameH\":34}],\"IsRotated\":true,\"IsTrimmed\":false,\"IsPremultiplied\":false}]");
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        EQUALS(zpl_array_count(r.nodes), 1);
        EQUALS(zpl_array_count(r.nodes[0].nodes), 7);
        EQUALS(r.nodes[0].nodes[3].type, ZPL_AST_TYPE_ARRAY);
        EQUALS(zpl_array_count(r.nodes[0].nodes[3].nodes), 8);

        __CLEANUP();
    });

    IT("parses geojson.io data", {
        zpl_string t = zpl_string_make(zpl_heap(), "{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[19.09149169921875,48.55786390423251],[19.172515869140625,48.55786390423251],[19.172515869140625,48.60101970261553],[19.09149169921875,48.60101970261553],[19.09149169921875,48.55786390423251]]]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"LineString\",\"coordinates\":[[19.149169921875,48.56024979174329],[16.63330078125,49.160154652338015],[18.28125,49.82380908513249],[18.720703125,49.210420445650286],[19.62158203125,48.929717630629554],[19.13818359375,48.58205840283824]]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Point\",\"coordinates\":[17.962646484375,48.17341248658084]}},{\"type\":\"Feature\",\"properties\":{},\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[18.4130859375,47.68388118858139],[19.951171875,47.00647991252098],[20.819091796874996,47.83159592699297],[19.237060546875,48.19904897935913],[18.380126953125,48.06706753191901],[17.633056640625,47.67648444221321],[17.764892578124996,47.21583707523794],[18.4130859375,47.68388118858139]]]}}]}");
        __PARSE(false);

        EQUALS(err, ZPL_JSON_ERROR_NONE);
        NEQUALS(zpl_array_count(r.nodes), 0);

        zpl_string_free(t);
        __CLEANUP();
    });

    IT("writes a complex JSON5 document", {
        zpl_string original = zpl_string_make(zpl_heap(), ""
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
        zpl_json_set_obj(&doc, NULL, zpl_heap());

        o = zpl_json_inset_str(&doc, "$api", "opengl");
        o = zpl_json_inset_str(&doc, "name", "Diffuse shader");
        o = zpl_json_inset_int(&doc, "version", 150);
        o = zpl_json_inset_str(&doc, "type", "fragment");
        o = zpl_json_inset_arr(&doc, "uniforms");
        {
            o2 = zpl_json_inset_obj(o, NULL);
            {
                zpl_json_inset_str(o2, "name", "l_pos");
                zpl_json_inset_str(o2, "type", "vec3");
            }
            o2 = zpl_json_inset_obj(o, NULL);
            {
                zpl_json_inset_str(o2, "name", "l_mat");
                zpl_json_inset_str(o2, "type", "mat4");
            }
        }
        o = zpl_json_inset_str(&doc, "_meta", "0 0 -34 2.34 123 2.34e-4");

        zpl_string a = zpl_json_write_string(zpl_heap(), &doc, 0);
        STREQUALS(original, a);
        zpl_string_free(a);
        zpl_string_free(original);
    });
});

#undef __PARSE
#undef __CLEANUP
