#ifndef GAME_H
#define GAME_H

#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../kernel/util.h"
#include "../drivers/vga.h"
#include "../kernel/gfx.h"

void game_init();
void game_update();
void game_draw();

extern bool single_player;

// static struct 
// {
    
// }game;


#endif