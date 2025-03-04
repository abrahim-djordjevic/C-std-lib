#include <stdarg.h>
#include <stdio.h>
#include "my_printf.h"

int main(void)
{
    int a = 200;
    // string test with no format
    my_printf("bababooey\n");
    // string test with format
    my_printf("%s\n", "bababooey");
    // char test
    my_printf("%c\n", 's');
    // decimal test
    my_printf("%d\n", a);
    // hex test
    my_printf("%x\n", a);
    // pointer test
    my_printf("%p\n", &a);
    // % char test
    my_printf("%%\n");
    // nothing test
    my_printf("%n\n");
}
