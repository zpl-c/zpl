////////////////////////////////////////////////////////////////
//
// Virtual Memory
//
//
#ifdef ZPL_EDITOR
#include <zpl.h>
#endif


typedef struct zpl_virtual_memory {
    void *data;
    zpl_isize size;
} zpl_virtual_memory;

//! Initialize virtual memory from existing data.
ZPL_DEF zpl_virtual_memory zpl_vm(void *data, zpl_isize size);

//! Allocate virtual memory at address with size.

//! @param addr The starting address of the region to reserve. If NULL, it lets operating system to decide where to allocate it.
//! @param size The size to server.
ZPL_DEF zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size);

//! Release the virtual memory.
ZPL_DEF zpl_b32 zpl_vm_free(zpl_virtual_memory vm);

//! Trim virtual memory.
ZPL_DEF zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size);

//! Purge virtual memory.
ZPL_DEF zpl_b32 zpl_vm_purge(zpl_virtual_memory vm);

//! Retrieve VM's page size and alignment.
ZPL_DEF zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out);
