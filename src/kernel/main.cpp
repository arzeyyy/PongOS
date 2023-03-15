#include "Rect.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"
#include "../../bordel/Text.h"
#include "../kernel/util.h"
#include "../pong/Game.h"
#include "idt.h"
#include "isr.h"

#define FPS 30
const float MS_PER_UPDATE = 1000.0f / FPS;

void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

void trigger_exception()
{
    //asm volatile("int $0x8");
    //asm volatile("int $0x0");

    // uint_8 a = 5;
    // uint_8 b = 0;
    // uint_8 c = a / b;
}

void init_kernel()
{
    // Initialize screen
    screen_init();

    // Initialize IDT and IRQ
    isr_init();
    sti();
    timer_init(FPS);
    init_keyboard();
}



void render()
{
    //clear
    clear();

    // draw
    // draw_pixel(319, 199, 255);
    //monitor_write("idk");
    // Font font;
    // font.setString("idk");
    // font.draw();



    //display
    swap_buffers();
}

extern "C" void main()
{

    init_kernel();

    // uint_8 a = 5;
    // uint_8 b = 0;
    // uint_8 c = a / b;

    trigger_exception();

    // Game game;
    // game.Init();
    init_system();

    // clear();
    // draw_pixel(319, 199, 255);
    // swap_buffers();
    // swap_buffers();

    // uint_8 array[SCREEN_SIZE];
    // memset(array, 0, SCREEN_SIZE);

    // screen_clear();
    // swap_buffers(); // swap double buffer
    

    float delta_time = 0.0f;
    uint_64 last_tick = timer_get();


    while (true)
    {
        // Delta time
        uint_64 curr_tick = timer_get();
        delta_time += (curr_tick - last_tick) / (float)state.freq;
        last_tick = curr_tick;

        // Update
        while (delta_time >= MS_PER_UPDATE)
        {
            //rect.move(10, 10);
            //update_game_state(MS_PER_UPDATE);
            delta_time -= MS_PER_UPDATE;
        }
        // clear
        //clear();

        // draw
        // draw_pixel(319, 199, 255);

        //rect.draw();

        // display
        //swap_buffers();

        render();  //clear, draw, swap
    }

    // while (true)
    // {
    //     float delta_time = get_delta_time();

    //     if (delta_time >= MS_PER_UPDATE) // draw frames at fixed timestep
    //     {
    //         clear();
    //         draw_pixel(319, 199, 255);
    //         swap_buffers();
    //         //draw_pixel(319, 199, 255);
      
    //         // Rect rect;
    //         // rect.setPosition(120, 120);
    //         // rect.setSize(10, 10);
    //         // rect.draw();    // calling draw pixel function
    //         //sti();
    //         //draw_frame();   // draw game state to buffer
    //         //cli();
    //         delta_time -= MS_PER_UPDATE;
    //     }

    //     //screen_clear();
    //     //draw_palette_tester();
    //     // draw_pixel(0, 0, 255);
    //     //game.Run();
    //     //scroll_screen();
    //     //sleep(50);
    // }

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
