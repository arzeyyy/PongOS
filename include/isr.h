#pragma once

#include "util.h"

#define NUM_ISRS 48

void isr_install();
extern "C" void isr_handler();
