// file: source/core/random.c


ZPL_BEGIN_C_DECLS

#if defined(ZPL_MODULE_THREADING)
zpl_global zpl_atomic32 zpl__random_shared_counter = {0};
#else
zpl_global zpl_i32 zpl__random_shared_counter = 0;
#endif

zpl_internal zpl_u32 zpl__get_noise_from_time(void) {
    zpl_u32 accum = 0;
    zpl_f64 start, remaining, end, curr = 0;
    zpl_u64 interval = 100000ll;
    
    start     = zpl_time_rel();
    remaining = (interval - cast(zpl_u64)(interval*start)%interval) / cast(zpl_f64)interval;
    end       = start + remaining;
    
    do {
        curr = zpl_time_rel();
        accum += cast(zpl_u32)curr;
    } while (curr >= end);
    return accum;
}

// NOTE: Partly from http://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/
// But the generation is even more random-er-est

zpl_internal ZPL_ALWAYS_INLINE zpl_u32 zpl__permute_qpr(zpl_u32 x) {
    zpl_local_persist zpl_u32 const prime = 4294967291; // 2^32 - 5
    if (x >= prime) {
        return x;
    } else {
        zpl_u32 residue = cast(zpl_u32)(cast(zpl_u64) x * x) % prime;
        if (x <= prime / 2)
            return residue;
        else
            return prime - residue;
    }
}

zpl_internal ZPL_ALWAYS_INLINE zpl_u32 zpl__permute_with_offset(zpl_u32 x, zpl_u32 offset) {
    return (zpl__permute_qpr(x) + offset) ^ 0x5bf03635;
}


void zpl_random_init(zpl_random *r) {
    zpl_u64 time, tick;
    zpl_isize i, j;
    zpl_u32 x = 0;
    r->value = 0;
    
    r->offsets[0] = zpl__get_noise_from_time();
#ifdef ZPL_MODULE_THREADING
    r->offsets[1] = zpl_atomic32_fetch_add(&zpl__random_shared_counter, 1);
    r->offsets[2] = zpl_thread_current_id();
    r->offsets[3] = zpl_thread_current_id() * 3 + 1;
#else
    r->offsets[1] = zpl__random_shared_counter++;
    r->offsets[2] = 0;
    r->offsets[3] = 1;
#endif
    time = zpl_time_tz_ms();
    r->offsets[4] = cast(zpl_u32)(time >> 32);
    r->offsets[5] = cast(zpl_u32)time;
    r->offsets[6] = zpl__get_noise_from_time();
    tick = zpl_rdtsc();
    r->offsets[7] = cast(zpl_u32)(tick ^ (tick >> 32));
    
    for (j = 0; j < 4; j++) {
        for (i = 0; i < zpl_count_of(r->offsets); i++) {
            r->offsets[i] = x = zpl__permute_with_offset(x, r->offsets[i]);
        }
    }
}

zpl_u32 zpl_random_gen_u32(zpl_random *r) {
    zpl_u32 x = r->value;
    zpl_u32 carry = 1;
    zpl_isize i;
    for (i = 0; i < zpl_count_of(r->offsets); i++) {
        x = zpl__permute_with_offset(x, r->offsets[i]);
        if (carry > 0) {
            carry = ++r->offsets[i] ? 0 : 1;
        }
    }
    
    r->value = x;
    return x;
}

zpl_u32 zpl_random_gen_u32_unique(zpl_random *r) {
    zpl_u32 x = r->value;
    zpl_isize i;
    r->value++;
    for (i = 0; i < zpl_count_of(r->offsets); i++) {
        x = zpl__permute_with_offset(x, r->offsets[i]);
    }
    
    return x;
}

zpl_u64 zpl_random_gen_u64(zpl_random *r) {
    return ((cast(zpl_u64)zpl_random_gen_u32(r)) << 32) | zpl_random_gen_u32(r);
}


zpl_isize zpl_random_gen_isize(zpl_random *r) {
#if defined(ZPL_ARCH_32_BIT)
    zpl_u32 u = zpl_random_gen_u32(r);
#else
    zpl_u64 u = zpl_random_gen_u64(r);
#endif
    zpl_isize i;
    zpl_memcopy(&i, &u, zpl_size_of(u));
    return i;
}


zpl_i64 zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc) {
    zpl_u64 u = zpl_random_gen_u64(r);
    zpl_i64 diff = higher_inc-lower_inc+1;
    u %= diff;
    zpl_i64 i;
    zpl_memcopy(&i, &u, zpl_size_of(u));
    i += lower_inc;
    return i;
}

zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc) {
#if defined(ZPL_ARCH_32_BIT)
    zpl_u32 u = zpl_random_gen_u32(r);
#else
    zpl_u64 u = zpl_random_gen_u64(r);
#endif
    zpl_isize diff = higher_inc-lower_inc+1;
    u %= diff;
    zpl_isize i;
    zpl_memcopy(&i, &u, zpl_size_of(u));
    i += lower_inc;
    return i;
}

ZPL_ALWAYS_INLINE zpl_f64 zpl__random_copy_sign64(zpl_f64 x, zpl_f64 y) {
    zpl_i64 ix=0, iy=0;
    zpl_memcopy(&ix, &x, zpl_size_of(zpl_i64));
    zpl_memcopy(&iy, &y, zpl_size_of(zpl_i64));
    
    ix &= 0x7fffffffffffffff;
    ix |= iy & 0x8000000000000000;
    
    zpl_f64 r = 0.0;
    zpl_memcopy(&r, &ix, zpl_size_of(zpl_f64));
    return r;
}

zpl_f64 zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc) {
    zpl_f64 f = cast(zpl_f64)zpl_random_gen_u64(r) / cast(zpl_f64)ZPL_U64_MAX;
    zpl_f64 diff = higher_inc-lower_inc;
    
    f *= diff;
    f += lower_inc;
    return f;
}

ZPL_END_C_DECLS
