#include "translation_b.h"

char* 
translation(int64_t num) {
    char* bin_num = malloc(sizeof(char) * (64 + 1));
    // check malloc
    for (int32_t i = 0; i < 64; ++i) {
        bin_num[i] = '0';
    }
    int32_t idx = 0;
    uint32_t bits_in_type = 64;
    int64_t mask = 1;
    mask = mask << (64 - 1);
    while (idx < 64 && num != 0) {
        bin_num[idx] = '0' + ((num & mask) != 0);
        num = num << 1;
        idx++;
    }
    bin_num[64] = '\0';
    return bin_num;
}