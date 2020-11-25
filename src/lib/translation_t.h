#pragma once
#include <stdint.h>
#include <stdlib.h>

// максимальная длина числа в триадах для типа int64
const int32_t MAX_TERNARY_LEN = 41;
/*
 * передовит число num из 10-ой системы счисления в 3-ую
 * результат возвращается в виде указателя на массив char, который выделяется в самой функции
 * в случае неуспеха возвращается NULL
 */
char*   translation(int64_t num);