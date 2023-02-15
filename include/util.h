#pragma once

#define FLAG_SET(x, flag) x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;
typedef uint_32 size_t;

void outb(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
void memset(void *ptr, uint_8 value, size_t num);
void *memcpy(void *dst, const void *src, size_t n);
char *strcpy(char *dest, const char *src);
