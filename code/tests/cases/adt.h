MODULE(adt, {
    IT("can build an ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_append_str(&root, "bar", "life");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");
    });
    IT("can build a deeper ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_append_str(&root, "bar", "life");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *array = zpl_adt_append_arr(&root, "numbers");
        zpl_adt_append_int(array, NULL, 1);
        zpl_adt_append_int(array, NULL, 2);
        zpl_adt_append_int(array, NULL, 3);
        EQUALS(root.nodes[2].nodes[2].integer, 3);
    });
    IT("can find a node within ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_append_str(&root, "bar", "life");
        zpl_adt_append_str(&root, "question", "answer");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *question_node = zpl_adt_find(&root, "question", false);
        STREQUALS(question_node->string, "answer");

    });
    IT("can find a node buried deep within ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_append_str(&root, "bar", "life");

        zpl_adt_node *level1, *level2;
        level1 = zpl_adt_append_obj(&root, "level1");
        level2 = zpl_adt_append_obj(level1, "level2");
        zpl_adt_append_str(level2, "question", "answer");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *question_node = zpl_adt_find(&root, "question", true);
        STREQUALS(question_node->string, "answer");

    });
    IT("can swap 2 nodes", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *n1 = zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_node *n2 = zpl_adt_append_str(&root, "bar", "life");
        zpl_adt_swap_nodes(n1, n2);
        EQUALS(root.nodes[1].integer, 42);
        STREQUALS(root.nodes[0].string, "life");
    });
    IT("can swap 2 nodes between 2 parents", {
        zpl_adt_node root, root2;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_set_obj(&root2, "root2", mem_alloc);
        zpl_adt_node *n1 = zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_node *n2 = zpl_adt_append_str(&root2, "bar", "life");
        zpl_adt_swap_nodes(n1, n2);
        EQUALS(root2.nodes[0].integer, 42);
        STREQUALS(root.nodes[0].string, "life");
    });
    IT("can remove a node from tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *n1 = zpl_adt_append_int(&root, "foo", 42);
        zpl_adt_remove_node(n1);
        EQUALS(zpl_array_count(root.nodes), 0);
    });
    IT("can move a node from one parent to another", {
        zpl_adt_node root, root2;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_set_obj(&root2, "root2", mem_alloc);
        zpl_adt_node *n1 = zpl_adt_append_int(&root, "foo", 42);
        EQUALS(root.nodes[0].integer, 42);
        EQUALS(zpl_array_count(root2.nodes), 0);
        zpl_adt_move_node(n1, &root2);
        EQUALS(root2.nodes[0].integer, 42);
        EQUALS(zpl_array_count(root.nodes), 0);
    });
    IT("can find a nested node in a tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *a = zpl_adt_append_obj(&root, "a");
        zpl_adt_node *b = zpl_adt_append_obj(a, "b");
        zpl_adt_node *c = zpl_adt_append_obj(b, "c");

        zpl_adt_node *node = zpl_adt_get(&root, "a/b/c");

        EQUALS(c, node);
    });
    IT("can find a node in an array where an object matches param=value", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *arr = zpl_adt_append_arr(&root, "arr");

        zpl_adt_node *a = zpl_adt_append_obj(arr, 0);
            zpl_adt_append_int(a, "foo", 456);
        zpl_adt_node *a2 = zpl_adt_append_obj(arr, 0);
            zpl_adt_append_int(a2, "foo", 123);
        zpl_adt_node *a3 = zpl_adt_append_obj(arr, 0);
            zpl_adt_append_int(a3, "foo", 789);
        zpl_adt_node *node = zpl_adt_get(&root, "arr/[foo=123]");

        EQUALS(a2, node);
    });
    IT("can retrieve a node in an array at a specific index", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *arr = zpl_adt_append_arr(&root, "arr");

        zpl_adt_append_int(arr, 0, 1);
        zpl_adt_append_int(arr, 0, 2);
        zpl_adt_append_int(arr, 0, 3);
        zpl_adt_node *node = zpl_adt_get(&root, "arr/1");

        EQUALS(2, node->integer);
    });
    IT("can find a node in an array of a specific value", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", mem_alloc);
        zpl_adt_node *arr = zpl_adt_append_arr(&root, "arr");

        zpl_adt_append_int(arr, "1", 1);
        zpl_adt_append_int(arr, "2", 2);
        zpl_adt_append_int(arr, "3", 3);
        zpl_adt_node *node = zpl_adt_get(&root, "arr/[2]");

        EQUALS(2, node->integer);
    });
});
