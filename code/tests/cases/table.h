ZPL_TABLE(static inline, unit_table, unit_table_, zpl_i32);

MODULE(table, {
    IT("should able to do basic table operations", {
        unit_table t1 = {0};
        unit_table_init(&t1, zpl_heap());

        unit_table_set(&t1, 0, 65);
        unit_table_set(&t1, 1, 66);
        unit_table_set(&t1, 2, 67);

        EQUALS(65, *unit_table_get(&t1, 0));
        EQUALS(66, *unit_table_get(&t1, 1));
        EQUALS(67, *unit_table_get(&t1, 2));

        unit_table_destroy(&t1);
    });

    IT("should able to grow if provided with more elements", {
        unit_table t1 = {0};
        unit_table_init(&t1, zpl_heap());

        for (int i = 0; i < 10; ++i) {
            unit_table_set(&t1, i, i+5);
        }

        unit_table_destroy(&t1);
    });

    IT("should able to work properly after being cleared", {
        unit_table t1 = {0};
        unit_table_init(&t1, zpl_heap());

        for (int i = 0; i < 10; ++i) {
            unit_table_set(&t1, i, i+5);
        }

        unit_table_clear(&t1);

        unit_table_set(&t1, 0, 65);
        unit_table_set(&t1, 1, 66);
        unit_table_set(&t1, 2, 67);

        EQUALS(65, *unit_table_get(&t1, 0));
        EQUALS(66, *unit_table_get(&t1, 1));
        EQUALS(67, *unit_table_get(&t1, 2));

        unit_table_destroy(&t1);
    });
});
