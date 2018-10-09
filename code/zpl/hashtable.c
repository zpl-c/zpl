/** @file hashtable.c
@brief Instantiated hash table

@n
@n This is an attempt to implement a templated hash table
@n NOTE: The key is always a u64 for simplicity and you will _probably_ _never_ need anything bigger.
@n
@n Hash table type and function declaration, call: ZPL_TABLE_DECLARE(PREFIX, NAME, N, VALUE)
@n Hash table function definitions, call: ZPL_TABLE_DEFINE(NAME, N, VALUE)
@n
@n     PREFIX  - a prefix for function prototypes e.g. extern, static, etc.
@n     NAME    - Name of the Hash Table
@n     FUNC    - the name will prefix function names
@n     VALUE   - the type of the value to be stored
@n
 @n tablename_init(NAME * h, zpl_allocator a);
 @n tablename_destroy(NAME * h);
  @n tablename_get(NAME * h, u64 key);
 @n tablename_set(NAME * h, u64 key, VALUE value);
@n tablename_grow(NAME * h);
  @n tablename_rehash(NAME * h, isize new_count);
 @n tablename_remove(NAME * h, u64 key);
*/

#define zpl_hash_table_find_result_t zpl_hash_table_find_result
typedef struct zpl_hash_table_find_result {
    isize hash_index;
    isize entry_prev;
    isize entry_index;
} zpl_hash_table_find_result;

#define ZPL_TABLE(PREFIX, NAME, FUNC, VALUE)                                                                           \
ZPL_TABLE_DECLARE(PREFIX, NAME, FUNC, VALUE);                                                                      \
ZPL_TABLE_DEFINE(NAME, FUNC, VALUE);

#define ZPL_TABLE_DECLARE(PREFIX, NAME, FUNC, VALUE)                                                                   \
typedef struct ZPL_JOIN2(NAME, Entry) {                                                                            \
    u64 key;                                                                                                       \
    isize next;                                                                                                    \
    VALUE value;                                                                                                   \
} ZPL_JOIN2(NAME, Entry);                                                                                          \
\
typedef struct NAME {                                                                                              \
    zpl_array(isize) hashes;                                                                                       \
    zpl_array(ZPL_JOIN2(NAME, Entry)) entries;                                                                     \
} NAME;                                                                                                            \
\
PREFIX void ZPL_JOIN2(FUNC, init)(NAME * h, zpl_allocator a);                                                      \
PREFIX void ZPL_JOIN2(FUNC, destroy)(NAME * h);                                                                    \
PREFIX VALUE *ZPL_JOIN2(FUNC, get)(NAME * h, u64 key);                                                             \
PREFIX void ZPL_JOIN2(FUNC, set)(NAME * h, u64 key, VALUE value);                                                  \
PREFIX void ZPL_JOIN2(FUNC, grow)(NAME * h);                                                                       \
PREFIX void ZPL_JOIN2(FUNC, rehash)(NAME * h, isize new_count);                                                    \
PREFIX void ZPL_JOIN2(FUNC, remove)(NAME * h, u64 key);

#define ZPL_TABLE_DEFINE(NAME, FUNC, VALUE)                                                                            \
void ZPL_JOIN2(FUNC, init)(NAME * h, zpl_allocator a) {                                                            \
    zpl_array_init(h->hashes, a);                                                                                  \
    zpl_array_init(h->entries, a);                                                                                 \
}                                                                                                                  \
\
void ZPL_JOIN2(FUNC, destroy)(NAME * h) {                                                                          \
    if (h->entries) zpl_array_free(h->entries);                                                                    \
    if (h->hashes) zpl_array_free(h->hashes);                                                                      \
}                                                                                                                  \
\
zpl_internal isize ZPL_JOIN2(FUNC, _add_entry)(NAME * h, u64 key) {                                                \
    isize index;                                                                                                   \
    ZPL_JOIN2(NAME, Entry) e = { 0 };                                                                              \
    e.key = key;                                                                                                   \
    e.next = -1;                                                                                                   \
    index = zpl_array_count(h->entries);                                                                           \
    zpl_array_append(h->entries, e);                                                                               \
    return index;                                                                                                  \
}                                                                                                                  \
\
zpl_internal zpl_hash_table_find_result ZPL_JOIN2(FUNC, _find)(NAME * h, u64 key) {                                \
    zpl_hash_table_find_result r = { -1, -1, -1 };                                                                 \
    if (zpl_array_count(h->hashes) > 0) {                                                                          \
        r.hash_index = key % zpl_array_count(h->hashes);                                                           \
        r.entry_index = h->hashes[r.hash_index];                                                                   \
        while (r.entry_index >= 0) {                                                                               \
            if (h->entries[r.entry_index].key == key) return r;                                                    \
            r.entry_prev = r.entry_index;                                                                          \
            r.entry_index = h->entries[r.entry_index].next;                                                        \
        }                                                                                                          \
    }                                                                                                              \
    return r;                                                                                                      \
}                                                                                                                  \
\
zpl_internal b32 ZPL_JOIN2(FUNC, _full)(NAME * h) {                                                                \
    return 0.75f * zpl_array_count(h->hashes) < zpl_array_count(h->entries);                                       \
}                                                                                                                  \
\
void ZPL_JOIN2(FUNC, grow)(NAME * h) {                                                                             \
    isize new_count = ZPL_ARRAY_GROW_FORMULA(zpl_array_count(h->entries));                                         \
    ZPL_JOIN2(FUNC, rehash)(h, new_count);                                                                         \
}                                                                                                                  \
\
void ZPL_JOIN2(FUNC, rehash)(NAME * h, isize new_count) {                                                          \
    isize i, j;                                                                                                    \
    NAME nh = { 0 };                                                                                               \
    ZPL_JOIN2(FUNC, init)(&nh, zpl_array_allocator(h->hashes));                                                    \
    zpl_array_resize(nh.hashes, new_count);                                                                        \
    zpl_array_reserve(nh.entries, zpl_array_count(h->entries));                                                    \
    for (i = 0; i < new_count; i++) nh.hashes[i] = -1;                                                             \
    for (i = 0; i < zpl_array_count(h->entries); i++) {                                                            \
        ZPL_JOIN2(NAME, Entry) * e;                                                                                \
        zpl_hash_table_find_result fr;                                                                             \
        if (zpl_array_count(nh.hashes) == 0) ZPL_JOIN2(FUNC, grow)(&nh);                                           \
        e = &h->entries[i];                                                                                        \
        fr = ZPL_JOIN2(FUNC, _find)(&nh, e->key);                                                                  \
        j = ZPL_JOIN2(FUNC, _add_entry)(&nh, e->key);                                                              \
        if (fr.entry_prev < 0)                                                                                     \
        nh.hashes[fr.hash_index] = j;                                                                          \
        else                                                                                                       \
        nh.entries[fr.entry_prev].next = j;                                                                    \
        nh.entries[j].next = fr.entry_index;                                                                       \
        nh.entries[j].value = e->value;                                                                            \
    }                                                                                                              \
    ZPL_JOIN2(FUNC, destroy)(h);                                                                                   \
    h->hashes = nh.hashes;                                                                                         \
    h->entries = nh.entries;                                                                                       \
}                                                                                                                  \
\
VALUE *ZPL_JOIN2(FUNC, get)(NAME * h, u64 key) {                                                                   \
    isize index = ZPL_JOIN2(FUNC, _find)(h, key).entry_index;                                                      \
    if (index >= 0) return &h->entries[index].value;                                                               \
    return NULL;                                                                                                   \
}                                                                                                                  \
\
void ZPL_JOIN2(FUNC, remove)(NAME * h, u64 key) {                                                                  \
    zpl_hash_table_find_result fr = ZPL_JOIN2(FUNC, _find)(h, key);                                                \
    if (fr.entry_index >= 0) {                                                                                     \
        if (fr.entry_prev >= 0) {                                                                                  \
            h->entries[fr.entry_prev].next = h->entries[fr.entry_index].next;                                      \
        } else {                                                                                                   \
            h->hashes[fr.hash_index] = fr.entry_index;                                                             \
        }                                                                                                          \
        zpl_array_remove_at(h->entries, fr.entry_index);                                                           \
    }                                                                                                              \
    ZPL_JOIN2(FUNC, rehash)(h, zpl_array_count(h->entries));                                                       \
}                                                                                                                  \
\
void ZPL_JOIN2(FUNC, set)(NAME * h, u64 key, VALUE value) {                                                        \
    isize index;                                                                                                   \
    zpl_hash_table_find_result fr;                                                                                 \
    if (zpl_array_count(h->hashes) == 0) ZPL_JOIN2(FUNC, grow)(h);                                                 \
    fr = ZPL_JOIN2(FUNC, _find)(h, key);                                                                           \
    if (fr.entry_index >= 0) {                                                                                     \
        index = fr.entry_index;                                                                                    \
    } else {                                                                                                       \
        index = ZPL_JOIN2(FUNC, _add_entry)(h, key);                                                               \
        if (fr.entry_prev >= 0) {                                                                                  \
            h->entries[fr.entry_prev].next = index;                                                                \
        } else {                                                                                                   \
            h->hashes[fr.hash_index] = index;                                                                      \
        }                                                                                                          \
    }                                                                                                              \
    h->entries[index].value = value;                                                                               \
    if (ZPL_JOIN2(FUNC, _full)(h)) ZPL_JOIN2(FUNC, grow)(h);                                                       \
}\

//$$

