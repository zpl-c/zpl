#define ZPL_IMPLEMENTATION
#define ZPL_ENT_IMPLEMENTATION
#include <zpl.h>
#include <zpl_ent.h>

typedef struct {
    f32 x,y,z;
} ZPL_ENT_COMP_DECLARE(transform);

// NOTE(ZaKlaus): Put this EXACTLY to one source file!
ZPL_ENT_COMP_DEFINE(transform);

int main(void) {
    
    // NOTE(ZaKlaus): Initialize our entity pool
    zpl_ent_pool_t pool = {0};
    zpl_ent_init(&pool, zpl_heap_allocator(), 100);
    
    // NOTE(ZaKlaus): Initialize our component pool
    // WARN(ZaKlaus): Component pool of type X can be used EXACTLY by ONE entity pool EXCLUSIVELY!!!
    transform_meta_t tranpool = {0};
    transform_init(&tranpool, &pool, zpl_heap_allocator());
    
    // NOTE(ZaKlaus): Generate some entities.
    for (isize i = 0; i < 15; ++i) {
        zpl_ent_create(&pool);
    }
    
    zpl_ent_id_t t = zpl_ent_create(&pool);
    ZPL_ASSERT(t.id == 15); // NOTE(ZaKlaus): This entity should be 16th.
    
    // TODO(ZaKlaus): Add component to entity
    transform_t *data = transform_attach(&tranpool, t, (transform_t) { 1, 2, 3 });
    
    // NOTE(ZaKlaus): Check on the data.
    transform_t *d = transform_fetch(&tranpool, t);
    ZPL_ASSERT(d->x == 1 && d->y == 2 && d->z == 3);
    
    // NOTE(ZaKlaus): Detach component from entity.
    // WARN(ZaKlaus): Do this each time when you destroy the entity!
    zpl_ent_destroy(&pool, t);
    
    // TODO(ZaKlaus): Remove entity
    zpl_ent_destroy(&pool, t);
    
    // NOTE(ZaKlaus): Add new entity
    t = zpl_ent_create(&pool);
    ZPL_ASSERT(t.id == 15 && t.generation == 1); // NOTE(ZaKlaus): This should be re-used entity.
    
    // NOTE(ZaKlaus): Release our resources
    transform_free(&tranpool);
    zpl_ent_free(&pool);
    
    return 0;
}
