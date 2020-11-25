#pragma once
#include <stdint.h>
#include <stdlib.h>

// максимальная длина числа в битах для типа int64
const int32_t MAX_BIT_LEN = 64;
/*
 * передовит число num из 10-ой системы счисления в 2-ую
 * результат возвращается в виде указателя на массив char, который выделяется в самой функции
 * в случае неуспеха возвращается NULL
 */
char*   translation(int64_t num);