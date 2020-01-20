// file: source/core/array.c

#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

ZPL_BEGIN_C_DECLS

ZPL_NEVER_INLINE void *zpl__array_set_capacity(void *array, zpl_isize capacity, zpl_isize element_size) {
    zpl_array_header *h = ZPL_ARRAY_HEADER(array);

    ZPL_ASSERT(element_size > 0);

    if (capacity == h->capacity) return array;

    if (capacity < h->count) {
        if (h->capacity < capacity) {
            zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(h->capacity);
            if (new_capacity < capacity) new_capacity = capacity;
            zpl__array_set_capacity(array, new_capacity, element_size);
        }
        h->count = capacity;
    }

    {
        zpl_isize size = zpl_size_of(zpl_array_header) + element_size * capacity;
        zpl_array_header *nh = cast(zpl_array_header *) zpl_alloc(h->allocator, size);
        zpl_memmove(nh, h, zpl_size_of(zpl_array_header) + element_size * h->count);
        nh->allocator = h->allocator;
        nh->count = h->count;
        nh->data = (char *)nh + 1;
        nh->capacity = capacity;
        zpl_free(h->allocator, h);
        return nh + 1;
    }
}

ZPL_END_C_DECLS
