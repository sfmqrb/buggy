#include "mini_proto.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Read entire stdin into buffer
    fseek(stdin, 0, SEEK_END);
    long sz = ftell(stdin);
    fseek(stdin, 0, SEEK_SET);
    if (sz <= 0) return 0;

    uint8_t *buf = malloc(sz);
    fread(buf, 1, sz, stdin);

    record_t *rec = NULL;
    size_t used = decode_record(buf, sz, &rec);
    if (used == 0) {
        fprintf(stderr, "decode failed\n");
        free(buf);
        return 1;
    }

    printf("Name: %s\nAge: %u\nScores:", rec->name, rec->age);
    for (uint32_t i = 0; i < rec->score_count; i++) {
        printf(" %u", rec->scores[i]);
    }
    printf("\n");

    // Re-encode
    size_t need = encode_record(rec, NULL, 0);
    uint8_t *out = malloc(need);
    size_t wrote = encode_record(rec, out, need);
    fwrite(out, 1, wrote, stdout);

    free(out);
    free_record(rec);
    free(buf);
    return 0;
}

