#include "mini_proto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int same_record(const record_t *a, const record_t *b) {
    if (strcmp(a->name, b->name) != 0) return 0;
    if (a->age != b->age) return 0;
    if (a->score_count != b->score_count) return 0;
    return memcmp(a->scores, b->scores, a->score_count * sizeof(uint16_t)) == 0;
}

int main(void) {
    record_t in = {0};
    strncpy(in.name, "alice", MAX_NAME - 1);
    in.age = 23;
    in.score_count = 3;
    uint16_t tmp_scores[] = {100, 250, 999};
    in.scores = tmp_scores;  // stack array OK for encode

    size_t need = encode_record(&in, NULL, 0);    // query size
    uint8_t *buf = malloc(need);
    size_t wrote = encode_record(&in, buf, need);
    if (wrote == 0) {
        fprintf(stderr, "encode failed\n");
        free(buf);
        return 1;
    }

    record_t *out = NULL;
    size_t used = decode_record(buf, wrote, &out);
    if (used == 0 || !out) {
        fprintf(stderr, "decode failed\n");
        free(buf);
        return 1;
    }


    printf("Name: %s\nAge: %u\nScores:", out->name, out->age);
    for (uint32_t i = 0; i < out->score_count; i++) printf(" %u", out->scores[i]);
    printf("\n");

    free(buf);
    free_record(out);  // frees heap-allocated scores + struct
    return 0;
}

