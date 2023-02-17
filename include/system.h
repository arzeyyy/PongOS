#pragma once

#include "util.h"
#include "../include/Graphics/vga.h"
#include "../include/Graphics/Font.h"

Font err_text;

void panic(const char *error);
