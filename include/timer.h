#pragma once

#include "util.h"
#include "../include/isr.h"

void init_timer(uint_32 frequency);
void timer_callback(registers_t regs);