#include "../include/Graphics/vga.h"
#include "../include/Graphics/Rect.h"
#include "../include/Text.h"
#include "../include/util.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define VGA_GRAPHICS_MODE 0x13

extern "C" void panic(){
    for(;;){}
}

void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

extern "C" void main()
{
    //Clear(BACKGROUND_BLUE | FOREGROUND_WHITE);
    //SetCursorPosition(PositionFromCords(0, 0));
    //printf("Hello world\n\rnew line", FOREGROUND_CYAN | BACKGROUND_BLUE);
    
    clear();
    screen_init();
    draw_palette_tester();
    //draw_pixel(319, 199, 0xFF);

    // Rect rect;
    // rect.setPosition(100, 100);
    // rect.setSize(10, 10);
    // rect.draw();


    // Rect rect1;
    // rect1.setPosition(50, 50);
    // rect1.setSize(20, 20);
    // rect1.draw();


    return;
}

