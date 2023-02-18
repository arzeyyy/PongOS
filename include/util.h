#pragma once

#define FLAG_SET(x, flag) x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)
#define NULL (0)

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;
typedef uint_32 size_t;

//write i/o port
void outb(unsigned short port, unsigned char val);
//read i/o port
unsigned char inb(unsigned short port);
//fill memory
void memset(void *ptr, uint_8 value, size_t num);
//memory copy
void *memcpy(void *dst, const void *src, size_t n);
//string copy
char *strcpy(char *dest, const char *src);
//string length
size_t strlen(const char *str);

void reverse(char str[], int length);
//intiger to string
char *toString(size_t num, bool hexadecimal = 0);
