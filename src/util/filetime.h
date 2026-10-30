#ifndef IMG2PNG_FILETIME_H
#define IMG2PNG_FILETIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Platform timestamp payload.  It is a struct rather than a raw buffer so the
 * size is part of the API: get_file_times() writes all 16 bytes, and a caller
 * that declared "uint8_t buf[8]" used to overflow its own stack frame. */
typedef struct { uint8_t bytes[16]; } img_timeblob_t;

/* Copy the creation time and last-write time of src_path onto dst_path.
 * Returns 0 on success, -1 on failure (not fatal for a conversion). */
int copy_file_times(const char *src_path, const char *dst_path);

/* Read creation + last-write times into the payloads, so they survive an
 * in-place overwrite. */
int get_file_times(const char *path, img_timeblob_t *ctime_out,
                   img_timeblob_t *mtime_out);
int set_file_times(const char *path, const img_timeblob_t *ctime,
                   const img_timeblob_t *mtime);


#ifdef __cplusplus
}
#endif

#endif
