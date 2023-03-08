#ifndef TIMER_H
#define TIMER_H

#include "../kernel/util.h"
#include "../kernel/isr.h"
#include "screen.h"

static struct
{
    uint_64 divisor;
    uint_64 ticks;
    uint_32 freq;
} state;

void timer_init(uint_32 frequency);
void sleep(uint_64 milliseconds);
uint_64 timer_get();

#endif