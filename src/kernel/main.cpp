#include "Rect.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"
#include "../../bordel/Text.h"
#include "../kernel/util.h"
#include "idt.h"
#include "isr.h"

void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

void trigger_exception()
{
    //asm volatile("int $0x3");
    //asm volatile("int $0x0");

    // uint_8 a = 5;
    // uint_8 b = 0;
    // uint_8 c = a / b;
}

void init_kernel()
{
    // Initialize screen
    screen_clear();
    screen_init();

    // Initialize IDT and IRQ
    isr_init();
    sti();
    timer_init(10);
    init_keyboard();
}

extern "C" void main()
{
    init_kernel();
    //draw_palette_tester();

    trigger_exception();
    while (true)
    {
        //scroll_screen();
        //sleep(50);
    }

    // while (1)
    // {
    //     for (int y = 0; y < SCREEN_HEIGHT; y++)
    //     {
    //         uint_8 color = (timer_get() + y) % 256;
    //         for (int x = 0; x < SCREEN_WIDTH; x++)
    //         {
    //             draw_pixel(x, y, color);
    //         }
    //     }
    //     screen_swap(); // Display the updated screen
    // }

        // irq_init();

        // Clear(BACKGROUND_BLUE | FOREGROUND_WHITE);
        // SetCursorPosition(PositionFromCords(0, 0));
        // printf("Hello world\n\rnew line", FOREGROUND_CYAN | BACKGROUND_BLUE);

        // monitor_write("helo: ");
        // monitor_write("hello");
        // monitor_write("\n");
        // monitor_write("helo: ");


        //  draw_palette_tester();
        //  draw_pixel(319, 199, 0xFF);

        // Rect rect;
        // rect.setPosition(100, 100);
        // rect.setSize(10, 10);
        // rect.draw();

        // Rect rect1;
        // rect1.setPosition(50, 50);
        // rect1.setSize(20, 20);
        // rect1.draw();

        // Font font;
        // font.setColor(123);
        // font.setPosition(10, 0);
        // // font.setOrigin(font.getLocalBounds().width / 2, font.getLocalBounds().height / 2);
        // // font.setString("PongOS\nnew line");
        // font.setString("                                 \n _____             _____ _____   \n|  _  |___ ___ ___|     |   __|  \n|   __| . |   | . |  |  |__   |  \n|__|  |___|_|_|_  |_____|_____|  \n              |___|              ");
        // font.draw();

        return;
}
