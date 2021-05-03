// file: source/core/memory_virtual.c

////////////////////////////////////////////////////////////////
//
// Virtual Memory
//
//

ZPL_BEGIN_C_DECLS

zpl_virtual_memory zpl_vm(void *data, zpl_isize size) {
    zpl_virtual_memory vm;
    vm.data = data;
    vm.size = size;
    return vm;
}

#if defined(ZPL_SYSTEM_WINDOWS)
    zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size) {
        zpl_virtual_memory vm;
        ZPL_ASSERT(size > 0);
        vm.data = VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        vm.size = size;
        return vm;
    }

    zpl_b32 zpl_vm_free(zpl_virtual_memory vm) {
        MEMORY_BASIC_INFORMATION info;
        while (vm.size > 0) {
            if (VirtualQuery(vm.data, &info, zpl_size_of(info)) == 0) return false;
            if (info.BaseAddress != vm.data || info.AllocationBase != vm.data || info.State != MEM_COMMIT ||
                info.RegionSize > cast(zpl_usize) vm.size) {
                return false;
            }
            if (VirtualFree(vm.data, 0, MEM_RELEASE) == 0) return false;
            vm.data = zpl_pointer_add(vm.data, info.RegionSize);
            vm.size -= info.RegionSize;
        }
        return true;
    }

    zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size) {
        zpl_virtual_memory new_vm = { 0 };
        void *ptr;
        ZPL_ASSERT(vm.size >= lead_size + size);

        ptr = zpl_pointer_add(vm.data, lead_size);

        zpl_vm_free(vm);
        new_vm = zpl_vm_alloc(ptr, size);
        if (new_vm.data == ptr) return new_vm;
        if (new_vm.data) zpl_vm_free(new_vm);
        return new_vm;
    }

    zpl_b32 zpl_vm_purge(zpl_virtual_memory vm) {
        VirtualAlloc(vm.data, vm.size, MEM_RESET, PAGE_READWRITE);
        // NOTE: Can this really fail?
        return true;
    }

    zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out) {
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        if (alignment_out) *alignment_out = info.dwAllocationGranularity;
        return info.dwPageSize;
    }

#else
#    include <sys/mman.h>

#    ifndef MAP_ANONYMOUS
#        define MAP_ANONYMOUS MAP_ANON
#    endif

    zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size) {
        zpl_virtual_memory vm;
        ZPL_ASSERT(size > 0);
        vm.data = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        vm.size = size;
        return vm;
    }

    zpl_b32 zpl_vm_free(zpl_virtual_memory vm) {
        munmap(vm.data, vm.size);
        return true;
    }

    zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size) {
        void *ptr;
        zpl_isize trail_size;
        ZPL_ASSERT(vm.size >= lead_size + size);

        ptr = zpl_pointer_add(vm.data, lead_size);
        trail_size = vm.size - lead_size - size;

        if (lead_size != 0) zpl_vm_free(zpl_vm(vm.data, lead_size));
        if (trail_size != 0) zpl_vm_free(zpl_vm(ptr, trail_size));
        return zpl_vm(ptr, size);
    }

    zpl_b32 zpl_vm_purge(zpl_virtual_memory vm) {
        int err = madvise(vm.data, vm.size, MADV_DONTNEED);
        return err != 0;
    }

    zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out) {
        // TODO: Is this always true?
        zpl_isize result = cast(zpl_isize) sysconf(_SC_PAGE_SIZE);
        if (alignment_out) *alignment_out = result;
        return result;
    }

#endif

ZPL_END_C_DECLS
