#pragma once

#include "util.h"

void irq_install(uint_8 num, void (*handler)(struct Registers *));
void irq_uninstall(uint_8 num);
void irq_init();

