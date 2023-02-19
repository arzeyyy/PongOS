#include "../include/Graphics/vga.h"
#include "../include/Graphics/Rect.h"
#include "../include/Graphics/Font.h"
#include "../include/Text.h"
#include "../include/util.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isr.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define VGA_GRAPHICS_MODE 0x13


void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

void trigger_exception()
{
    // int *ptr = nullptr;
    // *ptr = 1;
    asm volatile("int $0x3");
    //asm volatile("int $0x4");

    //__asm__(".byte 0xff, 0xff"); // invalid opcode

    //uint_8 a = 5;
    //uint_8 b = 0;
    //uint_8 c = a / b;
}

extern "C" void main()
{
    // Initialize IDT and IRQ

    idt_Init();
    isr_init();
    //irq_init();
    trigger_exception();


    // Clear(BACKGROUND_BLUE | FOREGROUND_WHITE);
    // SetCursorPosition(PositionFromCords(0, 0));
    // printf("Hello world\n\rnew line", FOREGROUND_CYAN | BACKGROUND_BLUE);

    clear();
    screen_init();
    // draw_palette_tester();
    // draw_pixel(319, 199, 0xFF);

    Rect rect;
    rect.setPosition(100, 100);
    rect.setSize(10, 10);
    rect.draw();

    Rect rect1;
    rect1.setPosition(50, 50);
    rect1.setSize(20, 20);
    rect1.draw();

    Font font;
    font.setColor(123);
    font.setPosition(10, 0);
    // font.setOrigin(font.getLocalBounds().width / 2, font.getLocalBounds().height / 2);
    // font.setString("PongOS\nnew line");
    font.setString("                                 \n _____             _____ _____   \n|  _  |___ ___ ___|     |   __|  \n|   __| . |   | . |  |  |__   |  \n|__|  |___|_|_|_  |_____|_____|  \n              |___|              ");
    font.draw();

    return;
}
