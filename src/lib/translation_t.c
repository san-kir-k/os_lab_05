#include "translation_t.h"

char* 
translation(int64_t num) {
    char* ternary_num = malloc(sizeof(char) * (41 + 1));
    // check malloc
    for (int32_t i = 0; i < 41; ++i) {
        ternary_num[i] = '0';
    }
    int32_t idx = 41 - 1;
    int8_t sign = (num < 0) ? -1 : 1; 
    num *= sign;
    while (num != 0) {
        ternary_num[idx] = '0' + num % 3;
        num /= 3;
        idx--;
    }
    if (sign < 0) {
        for (int32_t i = 0; i < 41; ++i) {
            if (ternary_num[i] == '0') {
                ternary_num[i] = '2';
            } else if (ternary_num[i] == '2') {
                ternary_num[i] = '0';
            }
        }
        if (ternary_num[41 - 1] == '0' || ternary_num[41 - 1] == '1') {
            ternary_num[41 - 1]++;
        } else {
            ternary_num[41 - 1] = '0';
            int32_t i; 
            for (i = 41 - 2; i >= 0 && ternary_num[i] == 2; --i) {
                ternary_num[i] = '0';
            }
            if (i >= 0) {
                ternary_num[i]++;
            }
        }
    }
    ternary_num[41] = '\0';
    return ternary_num;
}