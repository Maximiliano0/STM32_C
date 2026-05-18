#include <stdio.h>

char to_upper(char c);

int main(void)
{
    char in = 'l';

    char ucase = to_upper(in);
    printf("Uppercase: %c\n", ucase);

    return 0;
}

char to_upper(char c)
{
    char upper;

    upper = c - 32;
    upper = c - ('a' - 'A');

    return(upper);
}