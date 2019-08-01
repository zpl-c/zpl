/** @file misc.c
@brief Various other stuff
@defgroup misc Various other stuff

 Methods that don't belong anywhere but are still very useful in many occasions.
 
 @{
 */


typedef struct zpl_random {
    zpl_u32 offsets[8];
    zpl_u32 value;
} zpl_random;

// NOTE: Generates from numerous sources to produce a decent pseudo-random seed
ZPL_DEF void      zpl_random_init(zpl_random *r);
ZPL_DEF zpl_u32   zpl_random_gen_u32(zpl_random *r);
ZPL_DEF zpl_u32   zpl_random_gen_u32_unique(zpl_random *r);
ZPL_DEF zpl_u64   zpl_random_gen_u64(zpl_random *r); // NOTE: (zpl_random_gen_u32() << 32) | zpl_random_gen_u32()
ZPL_DEF zpl_isize zpl_random_gen_isize(zpl_random *r);
ZPL_DEF zpl_i64   zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc);
ZPL_DEF zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc);
ZPL_DEF zpl_f64   zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc);

ZPL_DEF void zpl_exit(zpl_u32 code);
ZPL_DEF void zpl_yield(void);

//! Returns allocated buffer
ZPL_DEF const char *zpl_get_env(const char *name);
ZPL_DEF const char *zpl_get_env_buf(const char *name);
ZPL_DEF zpl_string  zpl_get_env_str(const char *name);
ZPL_DEF void        zpl_set_env(const char *name, const char *value);
ZPL_DEF void        zpl_unset_env(const char *name);

ZPL_DEF zpl_u16 zpl_endian_swap16(zpl_u16 i);
ZPL_DEF zpl_u32 zpl_endian_swap32(zpl_u32 i);
ZPL_DEF zpl_u64 zpl_endian_swap64(zpl_u64 i);

ZPL_DEF zpl_isize zpl_count_set_bits(zpl_u64 mask);

ZPL_DEF zpl_u32    zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer);
ZPL_DEF zpl_string zpl_system_command_str(const char *command, zpl_allocator backing);

//! @}
//$$

////////////////////////////////////////////////////////////////
//
// Miscellany
//
//

#if ZPL_THREADING
zpl_global zpl_atomic32 zpl__random_shared_counter = {0};
#else
zpl_global zpl_i32 zpl__random_shared_counter = 0;
#endif

zpl_internal zpl_u32 zpl__get_noise_from_time(void) {
    zpl_u32 accum = 0;
    zpl_f64 start, remaining, end, curr = 0;
    zpl_u64 interval = 100000ll;
    
    start     = zpl_time_now();
    remaining = (interval - cast(zpl_u64)(interval*start)%interval) / cast(zpl_f64)interval;
    end       = start + remaining;
    
    do {
        curr = zpl_time_now();
        accum += cast(zpl_u32)curr;
    } while (curr >= end);
    return accum;
}

// NOTE: Partly from http://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/
// But the generation is even more random-er-est

zpl_internal zpl_inline zpl_u32 zpl__permute_qpr(zpl_u32 x) {
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

zpl_internal zpl_inline zpl_u32 zpl__permute_with_offset(zpl_u32 x, zpl_u32 offset) {
    return (zpl__permute_qpr(x) + offset) ^ 0x5bf03635;
}


void zpl_random_init(zpl_random *r) {
    zpl_u64 time, tick;
    zpl_isize i, j;
    zpl_u32 x = 0;
    r->value = 0;
    
    r->offsets[0] = zpl__get_noise_from_time();
#ifdef ZPL_THREADING
    r->offsets[1] = zpl_atomic32_fetch_add(&zpl__random_shared_counter, 1);
    r->offsets[2] = zpl_thread_current_id();
    r->offsets[3] = zpl_thread_current_id() * 3 + 1;
#else
    r->offsets[1] = zpl__random_shared_counter++;
    r->offsets[2] = 0;
    r->offsets[3] = 1;
#endif
    time = cast(zpl_u64)zpl_utc_time_now();
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
    zpl_u64 u = zpl_random_gen_u64(r);
    return *cast(zpl_isize *)&u;
}




zpl_i64 zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc) {
    zpl_u64 u = zpl_random_gen_u64(r);
    zpl_i64 i = *cast(zpl_i64 *)&u;
    zpl_i64 diff = higher_inc-lower_inc+1;
    i %= diff;
    i += lower_inc;
    return i;
}

zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc) {
    zpl_u64 u = zpl_random_gen_u64(r);
    zpl_isize i = *cast(zpl_isize *)&u;
    zpl_isize diff = higher_inc-lower_inc+1;
    i %= diff;
    i += lower_inc;
    return i;
}

zpl_f64 zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc) {
    zpl_u64 u = zpl_random_gen_u64(r);
    zpl_f64 f = *cast(zpl_f64 *)&u;
    zpl_f64 diff = higher_inc-lower_inc+1.0;
    f = zpl_mod64(f, diff);
    f += lower_inc;
    return f;
}



#if defined(ZPL_SYSTEM_WINDOWS)
zpl_inline void zpl_exit(zpl_u32 code) { ExitProcess(code); }
#else
zpl_inline void zpl_exit(zpl_u32 code) { exit(code); }
#endif

zpl_inline void zpl_yield(void) {
#if defined(ZPL_SYSTEM_WINDOWS)
    Sleep(0);
#else
    sched_yield();
#endif
}

zpl_inline const char *zpl_get_env(const char *name) {
    char *buffer = NULL;
    const char *ptr = zpl_get_env_buf(name);

    if (ptr == NULL) {
        return NULL;
    }

    zpl_isize ptr_size = zpl_strlen(ptr);
    buffer = (char *)zpl_malloc(ptr_size * sizeof(char)+1);
    zpl_memcopy((char *)buffer, ptr, ptr_size+1);
    return buffer;
}

zpl_inline const char *zpl_get_env_buf(const char *name) {
#ifdef ZPL_SYSTEM_WINDOWS
    zpl_local_persist char buffer[32767] = {0};
    if (!GetEnvironmentVariable(name, buffer, 32767)) {
        return NULL;
    }
    return (const char *)buffer;
#else
    return (const char *)getenv(name);
#endif
}

zpl_inline zpl_string zpl_get_env_str(const char *name) {
    const char *buf = zpl_get_env_buf(name);

    if (buf == NULL) {
        return NULL;
    }

    zpl_string str = zpl_string_make(zpl_heap(), buf);
    return str;
}

zpl_inline void zpl_set_env(const char *name, const char *value) {
#if defined(ZPL_SYSTEM_WINDOWS)
    SetEnvironmentVariableA(name, value);
#else
    setenv(name, value, 1);
#endif
}

zpl_inline void zpl_unset_env(const char *name) {
#if defined(ZPL_SYSTEM_WINDOWS)
    SetEnvironmentVariableA(name, NULL);
#else
    unsetenv(name);
#endif
}


zpl_inline zpl_u16 zpl_endian_swap16(zpl_u16 i) {
    return (i>>8) | (i<<8);
}

zpl_inline zpl_u32 zpl_endian_swap32(zpl_u32 i) {
    return (i>>24) |(i<<24) |
        ((i&0x00ff0000u)>>8)  | ((i&0x0000ff00u)<<8);
}

zpl_inline zpl_u64 zpl_endian_swap64(zpl_u64 i) {
    return (i>>56) | (i<<56) |
        ((i&0x00ff000000000000ull)>>40) | ((i&0x000000000000ff00ull)<<40) |
        ((i&0x0000ff0000000000ull)>>24) | ((i&0x0000000000ff0000ull)<<24) |
        ((i&0x000000ff00000000ull)>>8)  | ((i&0x00000000ff000000ull)<<8);
}


zpl_inline zpl_isize zpl_count_set_bits(zpl_u64 mask) {
    zpl_isize count = 0;
    while (mask) {
        count += (mask & 1);
        mask >>= 1;
    }
    return count;
}

#if !defined(ZPL_SYSTEM_WINDOWS)
extern char **environ;
#endif

zpl_inline zpl_u32 zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer) {
#if defined(ZPL_SYSTEM_EMSCRIPTEN)
    ZPL_PANIC("zpl_system_command not supported");
#else
    
#if defined(ZPL_SYSTEM_WINDOWS)
    FILE *handle = _popen(command, "r");
#else
    FILE *handle =  popen(command, "r");
#endif
    
    if(!handle) return 0;
    
    char c;
    zpl_usize i=0;
    while ((c = getc(handle)) != EOF && i++ < buffer_len) {
        *buffer++ = c;
    }
#if defined(ZPL_SYSTEM_WINDOWS)
    _pclose(handle);
#else
    pclose(handle);
#endif
    
#endif
    return 1;
}

zpl_inline zpl_string zpl_system_command_str(const char *command, zpl_allocator backing) {
#if defined(ZPL_SYSTEM_EMSCRIPTEN)
    ZPL_PANIC("zpl_system_command not supported");
#else
    
#if defined(ZPL_SYSTEM_WINDOWS)
    FILE *handle = _popen(command, "r");
#else
    FILE *handle =  popen(command, "r");
#endif
    
    if(!handle) return NULL;
    
    zpl_string output = zpl_string_make_reserve(backing, 4);
    
    char c;
    while ((c = getc(handle)) != EOF) {
        char ins[2] = {c,0};
        output = zpl_string_appendc(output, ins);
    }
    
    
    
#if defined(ZPL_SYSTEM_WINDOWS)
    _pclose(handle);
#else
    pclose(handle);
#endif
    
#endif
    return output;
}
