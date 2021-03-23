// file: source/core/file_tar.c


typedef struct {
  char name[100];
  char mode[8];
  char owner[8];
  char group[8];
  char size[12];
  char mtime[12];
  char checksum[8];
  char type;
  char linkname[100];
  char _padding[255];
} zpl__tar_header;

zpl_internal ZPL_ALWAYS_INLINE zpl_i64 zpl__tar_round_size(zpl_i64 n, zpl_i64 incr) {
    return n + (incr - n % incr) % incr;
}

zpl_internal zpl_usize zpl__tar_checksum(zpl__tar_header *hr) {
    zpl_usize i;
    zpl_usize res = 256;
    zpl_u8 *p = cast(zpl_u8*)(hr);
    for (i = 0; i < zpl_offset_of(zpl__tar_header, checksum); i++)
        res += p[i];
    for (i = zpl_offset_of(zpl__tar_header, type); i < zpl_size_of(zpl__tar_header); i++)
        res += p[i];
    return res;
}

zpl_internal zpl_b32 zpl__tar_write_null(zpl_file *archive, zpl_isize cnt) {
    char nil = 0;
    for (zpl_isize i = 0; i < cnt; i++) {
        if (!zpl_file_write(archive, &nil, 1))
            return 0;
    }
    return 1;
}

zpl_isize zpl_tar_pack(zpl_file *archive, char const **paths, zpl_isize paths_len) {
    ZPL_ASSERT_NOT_NULL(archive);
    ZPL_ASSERT_NOT_NULL(paths);

    for (zpl_isize i = 0; i < paths_len; i++) {
        ZPL_ASSERT_NOT_NULL(paths[i]);
        zpl__tar_header hr = {0};
        zpl_file file;
        zpl_file_error ferr = zpl_file_open_mode(&file, ZPL_FILE_MODE_READ, paths[i]);
        if (ferr == ZPL_FILE_ERROR_NOT_EXISTS) {
            return -(ZPL_TAR_ERROR_FILE_NOT_FOUND);
        } else if (ferr != ZPL_FILE_ERROR_NONE) {
            return -(ZPL_TAR_ERROR_IO_ERROR);
        }

        zpl_i64 file_size = zpl_file_size(&file);
        zpl_snprintf(hr.name, 12, "%s", paths[i]);
        zpl_snprintf(hr.size, 12, "%o", file_size);
        zpl_snprintf(hr.mode, 8, "%o", 0664);
        zpl_snprintf(hr.mtime, 12, "%o", zpl_fs_last_write_time(paths[i]));
        hr.type = ZPL_TAR_TYPE_REGULAR;
        zpl_snprintf(hr.checksum, 8, "%o", zpl__tar_checksum(&hr));

        zpl_file_write(archive, cast(void*)(&hr), zpl_size_of(zpl__tar_header));

        // write data
        {
            zpl_i64 remaining_data = file_size;
            zpl_i64 total_data = zpl__tar_round_size(remaining_data, 512);
            zpl_i64 padding = (total_data-file_size);
            char buf[4096] = {0};
            zpl_i64 pos = 0;
            zpl_isize bytes_read = 0;
            do {
                if (!zpl_file_read_at_check(&file, buf, 4096, pos, &bytes_read)) {
                    zpl_file_close(&file);
                    return -(ZPL_TAR_ERROR_IO_ERROR);
                } else if (bytes_read == 0) {
                    break;
                }

                zpl_file_write(archive, buf, bytes_read);
                pos += bytes_read;
                remaining_data -= bytes_read;
            }
            while (remaining_data > 0);

            if (padding > 0) {
                if (!zpl__tar_write_null(archive, padding)) {
                    zpl_file_close(&file);
                    return -(ZPL_TAR_ERROR_IO_ERROR);
                }
            }
        }

        zpl_file_close(&file);
    }

    if (!zpl__tar_write_null(archive, zpl_size_of(zpl__tar_header) * 2)) {
        return -(ZPL_TAR_ERROR_IO_ERROR);
    }

    return 0;
}

zpl_isize zpl_tar_unpack(zpl_file *archive, zpl_tar_unpack_proc *unpack_proc) {
    ZPL_ASSERT_NOT_NULL(archive);
    ZPL_ASSERT_NOT_NULL(unpack_proc);

    zpl_i64 pos = zpl_file_tell(archive);
    zpl_i64 begin_pos = pos;
    zpl__tar_header hr = {0};
    zpl_isize err = ZPL_TAR_ERROR_NONE;

    do {
        if (!zpl_file_read(archive, cast(void*)&hr, zpl_size_of(hr))) {
            err = ZPL_TAR_ERROR_IO_ERROR;
            break;
        }
        else if (*hr.checksum == 0) {
            break;
        }
        pos = zpl_file_tell(archive);

        zpl_tar_record rec = {0};
        rec.type = hr.type;
        rec.path = hr.name;
        rec.offset = pos;
        rec.length = zpl_str_to_i64(hr.size, 0, 8);
        rec.error = ZPL_TAR_ERROR_NONE;

        zpl_usize checksum1 = cast(zpl_usize)(zpl_str_to_i64(hr.checksum, 0, 8));
        zpl_usize checksum2 = zpl__tar_checksum(&hr);
        rec.error = (checksum1 != checksum2) ? cast(zpl_isize)ZPL_TAR_ERROR_BAD_CHECKSUM : rec.error;

        rec.error = unpack_proc(archive, &rec);

        if (rec.error > 0) {
            err = ZPL_TAR_ERROR_INTERRUPTED;
            break;
        }

        /* tar rounds files to 512 byte boundary */
        zpl_file_seek(archive, pos + zpl__tar_round_size(rec.length, 512));
    }
    while(err == ZPL_TAR_ERROR_NONE);

    zpl_file_seek(archive, begin_pos);
    return -(err);
}
