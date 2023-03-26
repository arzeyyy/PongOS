#include "keyboard.h"
#include "vga.h"
#include "../kernel/isr.h"


uint_8 keyboard_layout_us[2][128] = {
    {NULL, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
     '-', '=', KEY_BACKSPACE, KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u',
     'i', 'o', 'p', '[', ']', KEY_ENTER, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j',
     'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
     ',', '.', '/', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5,
     KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
     KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
     KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12},
    {KEY_NULL, KEY_ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
     '_', '+', KEY_BACKSPACE, KEY_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
     'I', 'O', 'P', '{', '}', KEY_ENTER, 0, 'A', 'S', 'D', 'F', 'G', 'H',
     'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
     'M', '<', '>', '?', 0, 0, 0, ' ', 0, KEY_F1, KEY_F2, KEY_F3, KEY_F4,
     KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, 0, 0, KEY_HOME, KEY_UP,
     KEY_PAGE_UP, '-', KEY_LEFT, '5', KEY_RIGHT, '+', KEY_END, KEY_DOWN,
     KEY_PAGE_DOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, KEY_F11, KEY_F12}};

// if (keyboard.key_down(23))

bool is_key_pressed(uint_8 key)
{
    // bool current_scancode = ;
    return keyboard.scancode == key;
}

uint_8 key_any()
{
    if(keyboard.scancode != NULL)
        return keyboard.scancode;

    else
    {
        return KEY_SPACE;
    }
}

// bool key_down(uint_8 key)
// {
//     if(!find(state.state_keys, key))
//     {

//         return true;
//     }
//     else{
//         return false;
//     }
// }

// bool key_up(uint_8 key)
// {
// }

const char *keycode;

void print_letter(uint_8 scancode)
{
    switch (scancode)
    {
    case 0x0:
        // monitor_write("ERROR");
        keycode = "ERROR";
        break;
    case 0x1:
        keycode = "ESC";
        // monitor_write("ESC");
        break;
    case 0x2:
        keycode = "1";
        // monitor_write("1");
        break;
    case 0x3:
        keycode = "2";
        // monitor_write("2");
        break;
    case 0x4:
        keycode = "3";
        // monitor_write("3");
        break;
    case 0x5:
        keycode = "4";
        // monitor_write("4");
        break;
    case 0x6:
        keycode = "5";
        // monitor_write("5");
        break;
    case 0x7:
        keycode = "6";
        // monitor_write("6");
        break;
    case 0x8:
        keycode = "7";
        // monitor_write("7");
        break;
    case 0x9:
        keycode = "8";
        // monitor_write("8");
        break;
    case 0x0A:
        keycode = "9";
        // monitor_write("9");
        break;
    case 0x0B:
        keycode = "0";
        // monitor_write("0");
        break;
    case 0x0C:
        keycode = "-";
        // monitor_write("-");
        break;
    case 0x0D:
        keycode = "+";
        // monitor_write("+");
        break;
    case 0x0E:
        keycode = "Backspace";
        // monitor_write("Backspace");
        break;
    case 0x0F:
        keycode = "Tab";
        // monitor_write("Tab");
        break;
    case 0x10:
        keycode = "Q";
        // monitor_write("Q");
        break;
    case 0x11:
        keycode = "W";
        // monitor_write("W");
        break;
    case 0x12:
        keycode = "E";
        // monitor_write("E");
        break;
    case 0x13:
        keycode = "R";
        // monitor_write("R");
        break;
    case 0x14:
        keycode = "T";
        // monitor_write("T");
        break;
    case 0x15:
        keycode = "Y";
        // monitor_write("Y");
        break;
    case 0x16:
        keycode = "U";
        // monitor_write("U");
        break;
    case 0x17:
        keycode = "I";
        // monitor_write("I");
        break;
    case 0x18:
        keycode = "O";
        // monitor_write("O");
        break;
    case 0x19:
        keycode = "P";
        // monitor_write("P");
        break;
    case 0x1A:
        keycode = "[";
        // monitor_write("[");
        break;
    case 0x1B:
        keycode = "]";
        // monitor_write("]");
        break;
    case 0x1C:
        keycode = "ENTER";
        // monitor_write("ENTER");
        break;
    case 0x1D:
        keycode = "LCtrl";
        // monitor_write("LCtrl");
        break;
    case 0x1E:
        // monitor_write("A");
        keycode = "A";
        break;
    case 0x1F:
        // monitor_write("S");
        keycode = "S";
        break;
    case 0x20:
        keycode = "D";
        // monitor_write("D");
        break;
    case 0x21:
        keycode = "F";
        // monitor_write("F");
        break;
    case 0x22:
        keycode = "G";
        // monitor_write("G");
        break;
    case 0x23:
        keycode = "H";
        // monitor_write("H");
        break;
    case 0x24:
        keycode = "J";
        // monitor_write("J");
        break;
    case 0x25:
        keycode = "K";
        // monitor_write("K");
        break;
    case 0x26:
        keycode = "L";
        // monitor_write("L");
        break;
    case 0x27:
        keycode = ";";
        // monitor_write(";");
        break;
    case 0x28:
        keycode = "'";
        // monitor_write("'");
        break;
    case 0x29:
        keycode = "`";
        // monitor_write("`");
        break;
    case 0x2A:
        keycode = "LShift";
        // monitor_write("LShift");
        break;
    case 0x2B:
        keycode = "\\";
        // monitor_write("\\");
        break;
    case 0x2C:
        keycode = "Z";
        // monitor_write("Z");
        break;
    case 0x2D:
        keycode = "X";
        // monitor_write("X");
        break;
    case 0x2E:
        keycode = "C";
        // monitor_write("C");
        break;
    case 0x2F:
        keycode = "V";
        // monitor_write("V");
        break;
    case 0x30:
        keycode = "B";
        // monitor_write("B");
        break;
    case 0x31:
        keycode = "N";
        // monitor_write("N");
        break;
    case 0x32:
        keycode = "M";
        // monitor_write("M");
        break;
    case 0x33:
        keycode = ",";
        // monitor_write(",");
        break;
    case 0x34:
        keycode = ".";
        // monitor_write(".");
        break;
    case 0x35:
        keycode = "/";
        // monitor_write("/");
        break;
    case 0x36:
        keycode = "Rshift";
        // monitor_write("Rshift");
        break;
    case 0x37:
        keycode = "Keypad * ";
        // monitor_write("Keypad *");
        break;
    case 0x38:
        keycode = "LAlt";
        // monitor_write("LAlt");
        break;
    case 0x39:
        keycode = "Spc";
        // monitor_write("Spc");
        break;
    default:
        /* 'keuyp' event corresponds to the 'keydown' + 0x80
         * it may still be a scancode we haven't implemented yet, or
         * maybe a control/escape sequence */
        if (scancode <= 0x7f)
        {
            monitor_write("Unknown key down");
        }
        else if (scancode <= 0x39 + 0x80)
        {
            // monitor_write("key up ");
            print_letter(scancode - 0x80);
        }
        else
            monitor_write("Unknown key up");
        break;
    }
}

static void keyboard_callback(registers_t regs)
{
    keyboard.scancode = inb(KEYBOARD_PORT);
    // monitor_write("sc: ");
    // monitor_write(to_string(keyboard.scancode));
    // monitor_write(",");
    // print_letter(keyboard.scancode);
    // monitor_write(keycode);
    // monitor_write("\n");
    
    

    // kprint("Keyboard scancode: ");
    // kprint(sc_ascii);
    // kprint(", ");
    // kprint("\n");
}

void init_keyboard()
{
    // monitor_write("Keyboard");
    keyboard.scancode = 0;
    isr_install(IRQ1, keyboard_callback);
}
