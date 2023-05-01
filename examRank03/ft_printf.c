#include <unistd.h>
#include <stdarg.h>

int putChar(int c)
{
    return (write(1, &c, 1));
}

int strLen(char *s)
{
    int i = 0;
    while (s[i])
        ++i;
    return (i);
}

int putStr(char *s)
{
    if (!s)
        return (write(1, "(null)", 6));
    return (write (1, s, strLen(s)));
}

void putNbrBase(long long int n, char *s, int base, int *count)
{
    if (n < 0)
    {
        *count += write(1, "-", 1);
        n *= -1;
    }
    if (n >= base)
        putNbrBase(n / base, s, base, count);
    *count += write(1, s + (n % base), 1);
}

int ft_printf(const char *s, ...)
{
    int count = 0;
    int i = 0;
    va_list args;
    va_start(args, s);
    while (s[i])
    {
        if (s[i] == '%')
        {
            ++i;
            if (s[i] == 'c')
                count += putChar(va_arg(args, int));
            else if (s[i] == 's')
                count += putStr(va_arg(args, char *));
            else if (s[i] == 'd' || s[i] == 'i')
                putNbrBase((long long int)va_arg(args, int), "0123456789", 10, &count);
            else if (s[i] == 'u')
                putNbrBase((long long int)va_arg(args, unsigned int), "0123456789", 10, &count);
            else if (s[i] == 'x')
                putNbrBase((long long int)va_arg(args, unsigned int), "0123456789abcdef", 16, &count);
            else if (s[i])
                count += write(1, s + i, 1);
            
        } else if (s[i]) {
            count += write(1, s + i, 1);
        }
        if (s[i])
            ++i;
    }
    return (count);
}

#include <stdio.h>
int main()
{
    int ret = printf("Hello %d%c%c%u%x%s%%%d %c%c %u %x %s\n", 42, '4', '2', 42, 42, "42", 42, '4', '2', 42, 42, "42");
    printf("printf ret = %d\n\n", ret);
    int ft_ret = ft_printf("Hello %d%c%c%u%x%s%%%d %c%c %u %x %s\n", 42, '4', '2', 42, 42, "42", 42, '4', '2', 42, 42, "42");
    printf("ft_printf ret = %d\n\n", ft_ret);
}
 

