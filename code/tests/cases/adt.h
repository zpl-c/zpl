MODULE(adt, {
    IT("can build an ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_inset_str(&root, "bar", "life");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");
        zpl_adt_destroy_branch(&root);
    });
    IT("can build a deeper ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_inset_str(&root, "bar", "life");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *array = zpl_adt_inset_arr(&root, "numbers");
        zpl_adt_inset_int(array, NULL, 1);
        zpl_adt_inset_int(array, NULL, 2);
        zpl_adt_inset_int(array, NULL, 3);
        EQUALS(root.nodes[2].nodes[2].integer, 3);
        zpl_adt_destroy_branch(&root);
    });
    IT("can find a node within ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_inset_str(&root, "bar", "life");
        zpl_adt_inset_str(&root, "question", "answer");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *question_node = zpl_adt_find(&root, "question", false);
        STREQUALS(question_node->string, "answer");

        zpl_adt_destroy_branch(&root);
    });
    IT("can find a node buried deep within ADT tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_inset_str(&root, "bar", "life");

        zpl_adt_node *level1, *level2;
        level1 = zpl_adt_inset_obj(&root, "level1");
        level2 = zpl_adt_inset_obj(level1, "level2");
        zpl_adt_inset_str(level2, "question", "answer");
        EQUALS(root.nodes[0].integer, 42);
        STREQUALS(root.nodes[1].string, "life");

        zpl_adt_node *question_node = zpl_adt_find(&root, "question", true);
        STREQUALS(question_node->string, "answer");

        zpl_adt_destroy_branch(&root);
    });
    IT("can swap 2 nodes", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_node *n1 = zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_node *n2 = zpl_adt_inset_str(&root, "bar", "life");
        zpl_adt_swap_nodes(n1, n2, &root);
        EQUALS(root.nodes[1].integer, 42);
        STREQUALS(root.nodes[0].string, "life");
        zpl_adt_destroy_branch(&root);
    });
    IT("can swap 2 nodes between 2 parents", {
        zpl_adt_node root, root2;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_set_obj(&root2, "root2", zpl_heap());
        zpl_adt_node *n1 = zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_node *n2 = zpl_adt_inset_str(&root2, "bar", "life");
        zpl_adt_swap_nodes_between_parents(n1, n2, &root, &root2);
        EQUALS(root2.nodes[0].integer, 42);
        STREQUALS(root.nodes[0].string, "life");
        zpl_adt_destroy_branch(&root);
        zpl_adt_destroy_branch(&root2);
    });
    IT("can remove a node from tree", {
        zpl_adt_node root;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_node *n1 = zpl_adt_inset_int(&root, "foo", 42);
        zpl_adt_remove_node(n1, &root);
        EQUALS(zpl_array_count(root.nodes), 0);
        zpl_adt_destroy_branch(&root);
    });
    IT("can move a node from one parent to another", {
        zpl_adt_node root, root2;
        zpl_adt_set_obj(&root, "root", zpl_heap());
        zpl_adt_set_obj(&root2, "root2", zpl_heap());
        zpl_adt_node *n1 = zpl_adt_inset_int(&root, "foo", 42);
        EQUALS(root.nodes[0].integer, 42);
        EQUALS(zpl_array_count(root2.nodes), 0);
        zpl_adt_move_node(n1, &root, &root2);
        EQUALS(root2.nodes[0].integer, 42);
        EQUALS(zpl_array_count(root.nodes), 0);
        zpl_adt_destroy_branch(&root);
        zpl_adt_destroy_branch(&root2);
    });
});
