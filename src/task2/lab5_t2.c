#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

#define SQR_LIB_CREATE_ERR 1
#define SQT_LIB_CREATE_ERR 2
#define TRB_LIB_CREATE_ERR 3
#define TRT_LIB_CREATE_ERR 4
#define SQR_LIB_CLOSE_ERR 5
#define SQT_LIB_CLOSE_ERR 6
#define TRB_LIB_CLOSE_ERR 7
#define TRT_LIB_CLOSE_ERR 8 

static const char* SQ_R_LIB = "libsquarer.so";
static const char* SQ_T_LIB = "libsquaret.so";
static const char* TR_B_LIB = "libtranslationb.so";
static const char* TR_T_LIB = "libtranslationt.so";

static const char* SQ_FUNC = "square";
static const char* TR_FUNC = "translation";

void 
usage() {
    printf("\t+-------------+-------------------------------------------+\n");
    printf("\t|   command   |               description                 |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|      0      |            switch realization             |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|-------------|        FISRT REALIZATION(default)         |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|    1 a b    |        calculate area of rectangle        |\n");
    printf("\t|             |              with sides a , b             |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|    2 num    | translate number to binary number system  |\n");
    printf("\t|             |        from decimal number system         |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|-------------|             SECOND REALIZATION            |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|    1 a b    |     calculate area of right triangle      |\n");
    printf("\t|             |            with sides a , b               |\n");
    printf("\t|-------------+-------------------------------------------|\n");
    printf("\t|    2 num    | translate number to ternary number system |\n");
    printf("\t|             |        from decimal number system         |\n");
    printf("\t+-------------+-------------------------------------------+\n\n");
}

void 
skip_str() {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void 
handler_loop(   void* dl_sqr_handle, void* dl_trb_handle, 
                void* dl_sqt_handle, void* dl_trt_handle) {
    float (*square)(float, float);
    char* (*translation)(int64_t);
    char* error = NULL;
    square = (float (*)(float, float))dlsym(dl_sqr_handle, SQ_FUNC);
    if ((error = dlerror()) != NULL)  {
        perror(error);
        return;
    }
    translation = (char* (*)(int64_t))dlsym(dl_trb_handle, TR_FUNC);
    if ((error = dlerror()) != NULL)  {
        perror(error);
        return;
    }
    int32_t cmd;
    int8_t ret_scanf_val = 0;
    int8_t realization = 0;
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
        case 0:
            if (realization == 0) {
                square = (float (*)(float, float))dlsym(dl_sqt_handle, SQ_FUNC);
                if ((error = dlerror()) != NULL)  {
                    perror(error);
                    return;
                }
                translation = (char* (*)(int64_t))dlsym(dl_trt_handle, TR_FUNC);
                if ((error = dlerror()) != NULL)  {
                    perror(error);
                    return;
                }
            } else {
                square = (float (*)(float, float))dlsym(dl_sqr_handle, SQ_FUNC);
                if ((error = dlerror()) != NULL)  {
                    perror(error);
                    return;
                }
                translation = (char* (*)(int64_t))dlsym(dl_trb_handle, TR_FUNC);

            }
            printf("Switched realizations from %d to %d.\n", realization + 1, (realization + 1) % 2 + 1);
            realization = (realization + 1) % 2;
            break;
        case 1:
            if ((ret_scanf_val = scanf("%f%f", &a, &b)) == EOF) {
                break;
            } else if (ret_scanf_val == 0) {
                printf("Invalid args, try again.\n");
                skip_str();
                break;
            }
            printf("Result is:\n%f\n", (*square)(a, b));
            break;
        case 2:
            if ((ret_scanf_val = scanf("%lld", &num)) == EOF) {
                break;
            } else if (ret_scanf_val == 0) {
                printf("Invalid args, try again.\n");
                skip_str();
                break;
            }
            char* returned_str = (*translation)(num);
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

int32_t
dylb_init(  void** dl_sqr_handle, void** dl_trb_handle, 
            void** dl_sqt_handle, void** dl_trt_handle) {
    *dl_sqr_handle = dlopen(SQ_R_LIB, RTLD_LAZY);
    if (!(*dl_sqr_handle)) {
        perror(dlerror());
        return SQR_LIB_CREATE_ERR;
    }
    *dl_trb_handle = dlopen(TR_B_LIB, RTLD_LAZY);
    if (!(*dl_trb_handle)) {
        if (dlclose((*dl_sqr_handle)) != 0) {
            fprintf(stderr, "Closing SQR lib error.");
        }
        perror(dlerror());
        return TRB_LIB_CREATE_ERR;
    }      
    *dl_sqt_handle = dlopen(SQ_T_LIB, RTLD_LAZY);
    if (!(*dl_sqt_handle)) {
        if (dlclose((*dl_sqr_handle)) != 0) {
            fprintf(stderr, "Closing SQR lib error.");
        } 
        if (dlclose((*dl_trb_handle)) != 0) {
            fprintf(stderr, "Closing TRB lib error.");
        }
        perror(dlerror());
        return SQT_LIB_CREATE_ERR;
    } 
    *dl_trt_handle = dlopen(TR_T_LIB, RTLD_LAZY);
    if (!(*dl_trt_handle)) {
        if (dlclose((*dl_sqr_handle)) != 0) {
            fprintf(stderr, "Closing SQR lib error.");
        } 
        if (dlclose((*dl_trb_handle)) != 0) {
            fprintf(stderr, "Closing TRB lib error.");
        }
        if (dlclose((*dl_sqt_handle)) != 0) {
            fprintf(stderr, "Closing SQT lib error.");
        }
        perror(dlerror());
        return TRT_LIB_CREATE_ERR;
    }  
    return 0;    
}

int32_t
dylb_close( void** dl_sqr_handle, void** dl_trb_handle, 
            void** dl_sqt_handle, void** dl_trt_handle) {
    int32_t to_return = 0;
    if (dlclose((*dl_sqr_handle)) != 0) {
        perror(dlerror());
        to_return = SQR_LIB_CLOSE_ERR;
    }
    if (dlclose((*dl_trb_handle)) != 0) {
        perror(dlerror());
        to_return = TRB_LIB_CLOSE_ERR;
    }
    if (dlclose((*dl_sqt_handle)) != 0) {
        perror(dlerror());
        to_return = SQT_LIB_CLOSE_ERR;
    }
    if (dlclose((*dl_trt_handle)) != 0) {
        perror(dlerror());
        to_return = TRT_LIB_CLOSE_ERR;
    }
    return to_return;
}

int 
main() {
    void* dl_sqr_handle = NULL;
    void* dl_trb_handle = NULL;
    void* dl_sqt_handle = NULL;
    void* dl_trt_handle = NULL;
    int32_t init_return = 0;
    if ((init_return = dylb_init(&dl_sqr_handle, &dl_trb_handle, &dl_sqt_handle, &dl_trt_handle)) != 0) {
        return init_return;
    }
    usage();
    handler_loop(dl_sqr_handle, dl_trb_handle, dl_sqt_handle, dl_trt_handle);
    int32_t close_return = 0;
    if ((close_return = dylb_close(&dl_sqr_handle, &dl_trb_handle, &dl_sqt_handle, &dl_trt_handle)) != 0) {
        return close_return;
    }
    return 0;
}
