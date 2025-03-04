#ifndef MY_PRINTF
#define MY_PRINTF

int print_char(int x);
int print_str(char * str);
int print_digit(long x, int base);
int my_printf(const char *char_ptr, ...);
int print_formatf(char specifier, va_list str);
int print_pointer(void * ptr);

#endif
