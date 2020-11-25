#include "translation_t.h"

char* 
translation(int64_t num) {
    char* ternary_num = malloc(sizeof(char) * (MAX_TERNARY_LEN + 1));
    if (ternary_num == NULL) {
        return NULL;
    }
    for (int32_t i = 0; i < MAX_TERNARY_LEN; ++i) {
        ternary_num[i] = '0';
    }
    int32_t idx = MAX_TERNARY_LEN - 1;
    int8_t sign = (num < 0) ? -1 : 1; 
    num *= sign;
    while (num != 0) {
        ternary_num[idx] = '0' + num % 3;
        num /= 3;
        idx--;
    }
    if (sign < 0) {
        for (int32_t i = 0; i < MAX_TERNARY_LEN; ++i) {
            if (ternary_num[i] == '0') {
                ternary_num[i] = '2';
            } else if (ternary_num[i] == '2') {
                ternary_num[i] = '0';
            }
        }
        if (ternary_num[MAX_TERNARY_LEN - 1] == '0' || ternary_num[MAX_TERNARY_LEN - 1] == '1') {
            ternary_num[MAX_TERNARY_LEN - 1]++;
        } else {
            ternary_num[MAX_TERNARY_LEN - 1] = '0';
            int32_t i; 
            for (i = MAX_TERNARY_LEN - 2; i >= 0 && ternary_num[i] == 2; --i) {
                ternary_num[i] = '0';
            }
            if (i >= 0) {
                ternary_num[i]++;
            }
        }
    }
    ternary_num[MAX_TERNARY_LEN] = '\0';
    return ternary_num;
}
