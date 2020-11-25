#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/translation_b.h"
#include "../lib/square_r.h"

void 
usage() {
    printf("\t+-------------+------------------------------------------+\n");
    printf("\t|   command   |               description                |\n");
    printf("\t|-------------+------------------------------------------|\n");
    printf("\t|-------------+------------------------------------------|\n");
    printf("\t|    1 a b    |        calculate area of rectangle       |\n");
    printf("\t|             |              with sides a , b            |\n");
    printf("\t|-------------+------------------------------------------|\n");
    printf("\t|    2 num    | translate number to binary number system |\n");
    printf("\t|             |        from decimal number system        |\n");
    printf("\t+-------------+------------------------------------------+\n\n");
}

void 
skip_str() {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void 
handler_loop() {
    int32_t cmd;
    int8_t ret_scanf_val = 0;
    while (true) {
        if ((ret_scanf_val = scanf("%d", &cmd)) == EOF) {
            break;
        } else if (ret_scanf_val == 0) {
            printf("Invalid cmd, try again.\n");
            skip_str();
            continue;
        }
        float a, b;
        int64_t num;
        switch (cmd) {
        case 1:
            if ((ret_scanf_val = scanf("%f%f", &a, &b)) == EOF) {
                break;
            } else if (ret_scanf_val != 2) {
                printf("Invalid args, try again.\n");
                skip_str();
                break;
            }
            if (a <= 0.0 || b <= 0.0) {
                printf("Sides must be positive, try again.\n");
                break;
            }
            printf("Result is:\n%f\n", square(a, b));
            break;
        case 2:
            if ((ret_scanf_val = scanf("%lld", &num)) == EOF) {
                break;
            } else if (ret_scanf_val == 0) {
                printf("Invalid args, try again.\n");
                skip_str();
                break;
            }
            char* returned_str = translation(num);
            if (returned_str == NULL) {
                perror("Memory allocation error.");
            }
            printf("Result is:\n%s\n", returned_str);
            free(returned_str);
            break;
        default:
            printf("Invalid cmd, try again.\n");
            break;
        }
    }
}

int 
main() {
    usage();
    handler_loop();
    return 0;
}
