#include "lib2.h"

static int lib2_var = 20;
extern int lib1_var;
extern int g_array[_MAX_BUFFER_SIZE];

void fun2(void) {
    // Example implementation of fun2
    printf("Hello from fun2!\n");
    printf("lib1_var = %d\n", lib1_var);

}

void fun3(int *arr, int size) {
    
    // imprimo array elements
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("g_array elements: ");
    for (int i = 0; i < sizeof(g_array) / sizeof(int); i++) {
        printf("%d ", g_array[i]);
    }

    printf("\n");
}