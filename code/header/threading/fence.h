// file: header/threading/fence.h

// Fences

ZPL_BEGIN_C_DECLS

ZPL_DEF void zpl_yield_thread(void);
ZPL_DEF void zpl_mfence      (void);
ZPL_DEF void zpl_sfence      (void);
ZPL_DEF void zpl_lfence      (void);

ZPL_END_C_DECLS
