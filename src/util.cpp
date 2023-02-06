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
