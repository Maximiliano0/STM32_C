#include "lib1.h"

int lib2_var = 30;
int g_array[_MAX_BUFFER_SIZE] = {10, 20, 30, 40, 50};
extern int lib1_var;

int main (void) {

    int *p;
    int local_array[] = {1, 2, 3, 4, 5};

    fun1();

    fun2();
    
    printf("lib1_var = %d\n", lib1_var);
    printf("lib2_var = %d\n", lib2_var);
    
    p = &lib2_var;
    printf("Value pointed to by p = %d\n", *p);

    p = &lib1_var;
    printf("Value pointed to by p = %d\n", *p); 

    fun3(local_array, sizeof(local_array) / sizeof(int));

    // imprimo g_array elements
    printf("g_array elements: ");
    for (int i = 0; i < sizeof(g_array) / sizeof(int); i++) {
        printf("%d ", g_array[i]);
    }

    return 0;
}