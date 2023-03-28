#include "../drivers/vga.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"
#include "../kernel/util.h"
#include "../pong/Game.h"
#include "../pong/menu.h"
#include "idt.h"
#include "isr.h"

#define FPS 30
const uint_64 frame_delay = 1000 / FPS;

void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;


void init_kernel()
{
    // Initialize screen
    vga_init();

    // Initialize IDT and IRQ
    isr_init();
    sti();
    timer_init(FPS);
    init_keyboard();
}

void render()
{
    // clear
    vga_clear();

    // update
    menu_update();

    // draw
    menu_draw();
}

extern "C" void main()
{
    init_kernel();

    uint_64 frame_start = 0;
    uint_64 frame_time = 0;

    while (true)
    {
        frame_start = timer_get();

        render();  //clear, draw, swap

        frame_time = timer_get() - frame_start;

        if(frame_delay > frame_time){
            sleep(frame_delay - frame_time);
        }
    }

    return;
}
