#include "../include/keyboard.h"
#include "../include/isr.h"
#include "../include/Window/monitor.h"
#include "../include/util.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

// US Keyboard Layout
static const char keyboard_layout[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, /* Caps lock */ 0, /* F1 */ 0, /* F2 */ 0, /* F3 */ 0, /* F4 */ 0, /* F5 */ 0, /* F6 */ 0, /* F7 */ 0, /* F8 */ 0, /* F9 */ 0, /* F10 */ 0, /* Num lock */ 0, /* Scroll lock */
    /* Home */ 0, /* Up */ 0, /* Page Up */ '-', 0, /* Left */ 0, 0, /* Right */ '+', 0, /* End */ 0, /* Down */ 0, /* Page Down */ 0, /* Insert */ 0, /* Delete */ 0, 0, 0, /* F11 */ 0, /* F12 */ 0};

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

// void handle_keyboard_input(uint_8 scan_code)
// {
//     static uint_8 caps_lock = 0;
//     static uint_8 shift = 0;

//     if (scan_code == BACKSPACE)
//     {
//         if (strlen(key_buffer) > 0)
//         {
//             key_buffer[strlen(key_buffer) - 1] = '\0';
//             monitor_backspace();
//         }
//     }
//     else if (scan_code == ENTER)
//     {
//         monitor_write("\n");
//         monitor_write(key_buffer);
//         memset(key_buffer, 0, sizeof(key_buffer));
//     }
//     else
//     {
//         char key = get_ascii_char(scan_code, caps_lock, shift);
//         if (key != '\0')
//         {
//             monitor_put(key);
//             strncat(key_buffer, &key, 1);
//         }
//     }
// }
void keyboard_callback(registers_t regs)
{
    uint_8 scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode > sizeof(keyboard_layout))
    {
        return;
    }

    char key = keyboard_layout[(int)scancode];
    if (key != 0)
    {
        monitor_write(toString(key));
    }
}

void init_keyboard()
{
    isr_install(IRQ1, &keyboard_callback);
}