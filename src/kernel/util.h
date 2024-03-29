#pragma once

#define FLAG_SET(x, flag) x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)
#define NULL (0)

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;
typedef uint_32 size_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef struct Vector2f {
    float x;
    float y;
} Vector2f;

typedef struct Vector2u {
    uint_32 x;
    uint_32 y;
} Vector2u;

enum colors
{
    COLOR_WHITE = 0xFF,
    COLOR_BLACK = 0x00,
    COLOR_GREY = 0x07,
    COLOR_RED = 0x40,
    COLOR_ORANGE = 0x42,
    COLOR_YELLOW = 0x43,
    COLOR_GREEN = 0x48,
    COLOR_CYAN = 0x4C,
    COLOR_BLUE = 0x4F,
    COLOR_PURPLE = 0x52,
};

// 0xFFFF = 11111111 8bit mask
#define low_16(address) (uint_16)((address) & 0xFFFF)  
// shift to right 
#define high_16(address) (uint_16)(((address) >> 16) & 0xFFFF)

// start interrupt
#define sti() asm volatile("sti")
// clear interrupt
#define cli() asm volatile("cli")

//write i/o port
void outb(unsigned short port, unsigned char val);
//read i/o port
unsigned char inb(unsigned short port);
//fill memory
void memset(void *ptr, uint_8 value, size_t num);
//memory copy
void *memcpy(void *dst, const void *src, size_t n);
//memory move
void memmove(void *dest, void *src, size_t n);
//string copy
char *strcpy(char *dest, const char *src);
//string length
size_t strlen(const char *str);

void to_ascii(int n, char str[]);

void reverse(char str[], int length);
//intiger to string
char *to_string(size_t num, bool hexadecimal = 0);

char *to_ascii(int num);

float smooth(float src, float dest, uint_64 time = 100);

int abs(int x);

// template <typename T>
//  bool find(auto array[], auto value);
Vector2f vector2f_new(float x, float y);
Vector2u vector2u_new(uint_32 x, uint_32 y);