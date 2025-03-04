#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>

int print_char(int x)
{
    return write(1, &x, 1);
}

int print_str(char * str)
{
    int count = 0;
    // use str + count to avoid 2 increments
    while(*(str + count))
    {
        print_char((int) *(str + count));
        ++count;
    }
    return count;
}

int print_digit(long x, int base)
{
    int count = 0;
    // create string of possible symbols for base 10 and base 16 numbers
    // symbols[n] will be n as a char
    const char *symbols = "0123456789abcdef";
    // negative number case
    // this will only be int print_formatf(char specifier, va_list str)
    //used for decimals as hex values are passed as unsigned ints
    if(x < 0)
    {
        print_char('-');                    // write minus sign
        return print_digit(-x, base) + 1;   // pass digit as positive value print it add one for minus
    }
    else if(x < base)
    {
        return print_char(symbols[x]);
    }
    else
    {
        count = print_digit(x / base, base);
        return count + print_digit(x % base, base);
    }
}

int print_pointer(void * ptr)
{
    uintptr_t uptr = (uintptr_t) ptr;
    return print_digit(uptr, 16);
}

int print_formatf(char specifier, va_list str)
{
    int count = 0;

    switch(specifier)
    {
        case('c'):
            count += print_char(va_arg(str, int));
            break;
        case('s'):
            count += print_str(va_arg(str, char*));
            break;
        case('d'):
            count += print_digit(va_arg(str, int), 10);
            break;
        case('x'):
            count += print_digit(va_arg(str, unsigned int), 16);
            break;
        case('p'):
            count += print_pointer(va_arg(str, void *));
            break;
        case('n'):
            break;
        case('%'):
        default:
            count += write(1, &specifier, 1);
            break;
    }
    return count;
}


int my_printf(const char *char_ptr, ...)
{
    va_list str;
    va_start(str, char_ptr);
    int count = 0;
    // check if dereferenced ptr ASCII code equals 0, ASCII code 0 is NULL
    while(*char_ptr != 0)
    {
        // check if current char is %
        if(*char_ptr == '%')
        {
            // pass character after incrementing char_ptr
            print_formatf(*(++char_ptr), str);
        }
        else
        {
            count += write(1, char_ptr, 1);
        }
        ++char_ptr; // move pointer
    }
    va_end(str);
    return count;
}
