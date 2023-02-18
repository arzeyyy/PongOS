#include "../include/util.h"

void outb(unsigned short port, unsigned char data) // write to i/o port
{
    asm volatile("outb %0, %1"          // %0, %1 placeholders for order %0 = data, %1 = port
    : :  "a"(data), "Nd"(port));        // "a" input constraint, 'data' are passed to 'a' register then  %0, %1 writes the value stored in 'a' register to 'port'
}

unsigned char inb(unsigned short port)  // read from i/o port
{
    unsigned char returnData;    
    asm volatile("inb %1, %0"           // %0 refers to returnData, %1 refers to port, inb %1, %0 reads data from 'port' and store it in 'a' register
    : "=a"(returnData) : "Nd"(port));   // "=a" output constraint, store the data from 'a' register to 'returnData'

    return returnData;
}

void memset(void *ptr, uint_8 value, size_t num)
{
    char *p = (char *)ptr;
    for (size_t i = 0; i < num; i++)
    {
        *(p + i) = value;
    }
}

void *memcpy(void *dst, const void *src, size_t n) {
    char *dst_ptr = (char *)dst;
    const char *src_ptr = (const char *)src;

    for (size_t i = 0; i < n; i++) {
      dst_ptr[i] = src_ptr[i];
    }

    return dst;
}

char *strcpy(char *dest, const char *src)
{
    int char_counter = 0;
    
    while (src[char_counter] != '\0')
    {
        dest[char_counter] = src[char_counter];
        char_counter++;
    }
    dest[char_counter] = '\0';
    return (dest);
}

size_t strlen(const char *str)
{
    size_t length = 0;
    while (*str != 0)
    {
        length++;
    }

    return length;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char *toString(size_t num, bool hexadecimal)
{
    if(hexadecimal == true)
    {
        static char buffer[33]; // max 32 bit integer
        int i = 30;
        buffer[31] = '\0';
        bool is_negative = false;
        if (num < 0)
        {
            is_negative = true;
            num = -num;
        }
        if (num == 0)
        {
            buffer[30] = '0';
            return &buffer[30];
        }
        while (num != 0 && i)
        {
            buffer[i--] = "0123456789abcdef"[num % 16];
            num /= 16;
        }
        if (is_negative)
        {
            buffer[i--] = '-';
        }
        return &buffer[i + 1];
    }

    static char str[20]; // Make sure this is large enough to hold the largest possible number
    int i = 0;
    bool isNegative = false;

    // Handle negative numbers
    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }

    // Convert the number to a string in reverse order
    while (num != 0)
    {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Add the negative sign if needed
    if (isNegative)
    {
        str[i++] = '-';
    }

    // Terminate the string
    str[i] = '\0';

    // Reverse the string
    reverse(str, i);

    // Return the string
    return str;
}
