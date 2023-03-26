#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../kernel/util.h"

#define KEYBOARD_PORT 0x60
#define KEY_MOD_ALT 0x0200
#define KEY_MOD_CTRL 0x0400
#define KEY_MOD_SHIFT 0x0800
#define KEY_MOD_CAPS_LOCK 0x1000
#define KEY_MOD_NUM_LOCK 0x2000
#define KEY_MOD_SCROLL_LOCK 0x4000
#define KEYBOARD_RELEASE 0x80

enum keycode
{
    KEY_1 = 0x02, 
    KEY_2 = 0x03, 
    KEY_3 = 0x04, 
    KEY_4 = 0x05, 
    KEY_5 = 0x06, 
    KEY_6 = 0x07, 
    KEY_7 = 0x08,
    KEY_8 = 0x09, 
    KEY_9 = 0x0A, 
    KEY_Q = 0x10,


    KEY_W = 0x11,
    KEY_E = 0x12,
    KEY_R = 0x13,
    KEY_T = 0x14,
    KEY_Z = 0x15,
    KEY_U = 0x16,
    KEY_I = 0x17,
    KEY_O = 0x18,
    KEY_P = 0x19,
    KEY_A = 0x1E,
    KEY_S = 0x1F,
    KEY_D = 0x20,
    KEY_F = 0x21,
    KEY_G = 0x22,
    KEY_H = 0x23,
    KEY_J = 0x24,
    KEY_K = 0x25,
    KEY_L = 0x26,
    KEY_Y = 0x2C,
    KEY_X = 0x2D,
    KEY_C = 0x2E,
    KEY_V = 0x2F,
    KEY_B = 0x30,
    KEY_N = 0x31,
    KEY_M = 0x32,

    KEY_NULL = 0x0,
    KEY_ESC = 27,
    KEY_SPACE = 0x39,
    KEY_BACKSPACE = '\b',
    KEY_TAB = '\t',
    KEY_ENTER = '\n',
    KEY_RETURN = '\r',
    KEY_INSERT = 0x90,
    KEY_DELETE = 0x91,
    KEY_HOME = 0x92,
    KEY_END = 0x9,
    KEY_PAGE_UP = 0x94,
    KEY_PAGE_DOWN = 0x95,
    KEY_LEFT = 0x4B,
    KEY_UP = 0x48,
    KEY_RIGHT = 0x4D,
    KEY_DOWN = 0x50,
    KEY_F1 = 0x80,
    KEY_F2 = (KEY_F1 + 1),
    KEY_F3 = (KEY_F1 + 2),
    KEY_F4 = (KEY_F1 + 3),
    KEY_F5 = (KEY_F1 + 4),
    KEY_F6 = (KEY_F1 + 5),
    KEY_F7 = (KEY_F1 + 6),
    KEY_F8 = (KEY_F1 + 7),
    KEY_F9 = (KEY_F1 + 8),
    KEY_F10 = (KEY_F1 + 9),
    KEY_F11 = (KEY_F1 + 10),
    KEY_F12 = (KEY_F1 + 11),
    KEY_LCTRL = 0x1D,
    KEY_RCTRL = 0x1D,
    KEY_LALT = 0x38,
    KEY_RALT = 0x38,
    KEY_LSHIFT = 0x2A,
    KEY_RSHIFT = 0x36,
    KEY_CAPS_LOCK = 0x3A,
    KEY_SCROLL_LOCK = 0x46,
    KEY_NUM_LOCK = 0x45,

};

// void init_keyboard();

// static struct
// {
//     const char *keycode;
//     uint_8 state_keys[];
// }state;


static struct
{
    uint_8 scancode;
    //bool (*is_key_pressed)(uint_8 key);
} keyboard;

// #endif

#define KEYBOARD_PORT 0x60


bool is_key_pressed(uint_8 key);
void init_keyboard();
uint_8 key_any();

#endif