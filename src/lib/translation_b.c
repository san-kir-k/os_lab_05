#include "translation_b.h"

char* 
translation(int64_t num) {
    char* bin_num = malloc(sizeof(char) * (MAX_BIT_LEN + 1));
    if (bin_num == NULL) {
        return NULL;
    }
    for (int32_t i = 0; i < MAX_BIT_LEN; ++i) {
        bin_num[i] = '0';
    }
    int32_t idx = 0;
    int64_t mask = 1;
    mask = mask << (MAX_BIT_LEN - 1);
    while (idx < MAX_BIT_LEN && num != 0) {
        bin_num[idx] = '0' + ((num & mask) != 0);
        num = num << 1;
        idx++;
    }
    bin_num[MAX_BIT_LEN] = '\0';
    return bin_num;
}
