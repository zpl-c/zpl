////////////////////////////////////////////////////////////////
//
// Linked List
//
// zpl_list encapsulates pointer to data and points to the next and the previous element in the list.
//
// Available Procedures for zpl_list
// zpl_list_init
// zpl_list_add
// zpl_list_remove
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif

#if 0
#define ZPL_IMPLEMENTATION
#include "zpl.h"
int main(void)
{
    zpl_list s, *head, *cursor;
    zpl_list_init(&s, "it is optional to call init: ");
    head = cursor = &s;

    // since we can construct an element implicitly this way
    // the second field gets overwritten once we add it to a list.
    zpl_list a = {"hello"};
    cursor = zpl_list_add(cursor, &a);

    zpl_list b = {"world"};
    cursor = zpl_list_add(cursor, &b);

    zpl_list c = {"!!! OK"};
    cursor = zpl_list_add(cursor, &c);

    for (zpl_list *l=head; l; l=l->next) {
        zpl_printf("%s ", cast(char *)l->ptr);
    }
    zpl_printf("\n");

    return 0;
}
#endif


typedef struct zpl__list {
    void const *ptr;
    struct zpl__list *next, *prev;
} zpl_list;

ZPL_DEF_INLINE void      zpl_list_init(zpl_list *list, void const *ptr);
ZPL_DEF_INLINE zpl_list *zpl_list_add(zpl_list *list, zpl_list *item);

// NOTE(zaklaus): Returns a pointer to the next node (or NULL if the removed node has no trailing node.)
ZPL_DEF_INLINE zpl_list *zpl_list_remove(zpl_list *list);


ZPL_INLINE void zpl_list_init(zpl_list *list, void const *ptr) {
    zpl_list list_ = { 0 };
    *list = list_;
    list->ptr = ptr;
}

ZPL_INLINE zpl_list *zpl_list_add(zpl_list *list, zpl_list *item) {
    item->next = NULL;

    if (list->next) { item->next = list->next; }

    list->next = item;
    item->prev = list;
    return item;
}

ZPL_INLINE zpl_list *zpl_list_remove(zpl_list *list) {
    if (list->prev) { list->prev->next = list->next; }

    return list->next;
}
