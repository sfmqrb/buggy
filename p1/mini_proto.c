#include "mini_proto.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t encode_record(const record_t *rec, uint8_t *out_buf, size_t out_cap) {
    /* Layout:
       [name_len:1][name_bytes][age:1][score_count:4][scores:2*score_count]
     */

    size_t name_len = strlen(rec->name);         // BUG: no bounds check vs MAX_NAME
    size_t need = 1 + name_len + 1 + 4 + 2 * rec->score_count;

    if (!out_buf) return need;

    if (need > out_cap) {
        // BUG: write anyway (overflow)
        // real code should return 0 or error
    }

    size_t off = 0;
    out_buf[off++] = (uint8_t)name_len;
    memcpy(out_buf + off, rec->name, name_len); off += name_len;

    out_buf[off++] = rec->age;

    // BUG: host endianness assumed
    memcpy(out_buf + off, &rec->score_count, 4); off += 4;

    // BUG: no check scores != NULL when score_count>0
    memcpy(out_buf + off, rec->scores, 2 * rec->score_count);
    off += 2 * rec->score_count;

    return off;
}

size_t decode_record(const uint8_t *buf, size_t len, record_t **out) {
    size_t off = 0;
    if (len < 1) return 0;
    uint8_t name_len = buf[off++];

    if (len < off + name_len + 1 + 4) return 0; // minimal check

    record_t *rec = malloc(sizeof(record_t));
    // BUG: no memset, stale pointers possible
    if (!rec) return 0;

    // BUG: name_len may exceed MAX_NAME and overflow rec->name
    memcpy(rec->name, buf + off, name_len);
    rec->name[name_len] = '\0';
    off += name_len;

    rec->age = buf[off++];

    memcpy(&rec->score_count, buf + off, 4); off += 4;

    // BUG: integer overflow: rec->score_count * 2 may overflow size_t
    size_t need = rec->score_count * 2;
    if (len < off + need) {
        // BUG: leak rec on error
        return 0;
    }

    rec->scores = malloc(need);
    // BUG: no NULL check
    memcpy(rec->scores, buf + off, need);
    off += need;

    *out = rec;
    return off;
}

void free_record(record_t *rec) {
    if (!rec) return;
    free(rec->scores);
    free(rec);
}

