#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <n7OS/keyboard.h>
#include <n7OS/console.h>
#include <n7OS/snake.h>

uint8_t c;

char keyMap[] = {
    'null', // 0
    '&',    // 1
    'é',    // 2
    '"',    // 3
    '\'',   // 4
    '(',    // 5
    '-',    // 6
    'è',    // 7
    '_',    // 8
    'ç',    // 9
    'à',    // 10
    ')',    // 11
    '=',    // 12
    '\b',   // 13 Backspace
    '\t',   // 14 Tab
    'a',    // 15
    'z',    // 16
    'e',    // 17
    'r',    // 18
    't',    // 19
    'y',    // 20
    'u',    // 21
    'i',    // 22
    'o',    // 23
    'p',    // 24
    '^',    // 25
    '$',    // 26
    '\n',   // 27 Enter
    'CTRL', // 28 crtl
    'q',    // 29
    's',    // 30
    'd',    // 31
    'f',    // 32
    'g',    // 33
    'h',    // 34
    'j',    // 35
    'k',    // 36
    'l',    // 37
    'm',    // 38
    '?',    // 39
    '²',    // 40
    'maj',  // 41 majuscule
    '*',    // 42
    'w',    // 43
    'x',    // 44
    'c',    // 45
    'v',    // 46
    'b',    // 47
    'n',    // 48
    ',',    // 48
    ';',    // 49
    ':',    // 50
    '!',    // 51
    '/',    // 52
    '*',    // 53
    'T',    // 54
    ' ',    // 55
    'altgr',// 56
    'F1',   // 57
    'F2',   // 58
    'F3',   // 59
    'F4',   // 60
    'F5',   // 61
    'F6',   // 62
    'F7',   // 63
    'F8',   // 64
    'F9',   // 65
    'F10',  // 66
    'VN',   // 67 verr num
    'L',    // 68
    '7',    // 69
    '8',    // 70
    '9',    // 71
    '-',    // 72
    '4',    // 73
    '5',    // 74
    '6',    // 75
    '+',    // 76
    '1',    // 77
    '2',    // 78
    '3',    // 79
    '0',    // 80
    '.',    // 81
    '6',    // 82
    '7',    // 83
    'page', // 84
    'F11',  // 85
    'F12',  // 86
    '+',    // 87
    '-',    // 88
    '.',    // 89
    '/'     // 90
};

void init_keyboard() {
    outb(0x21, 0x21);
}

void activer_keyboard() {
    outb(inb(0x21) & (1 << 0x21), 0x21);
}

void desactiver_keyboard() {
    outb(inb(0x21) | 0x02, 0x21);
}

void update_keyboard() {
    c = inb(0x60);
    if (c < 0x80) {
        switch (c) {
            case 0x2A:
                // touche shift
                break;
            case 0x36:
                // touche shift
                break;
            case 0x1D:
                // touche ctrl
                break;
            case 0x38:
                // touche alt
                break;
            case 0x3A:
                // touche maj
                break;
            case 0x45:
                // touche verr num
                break;
            case 0x46:
                // touche verr maj
                break;
            case 0x0E:
                // touche backspace
                if (get_cursor() > 0) {
                    set_cursor(get_cursor()-1);
                    printf(" ");
                    set_cursor(get_cursor()-1);
                }
                break;
            case 51:
                //mainSnake();
                break;
            default:
                printf("%c",keyMap[c-1]);
                break;
        }
        //touche enfoncee
        
    } else {
        //printf("Touche relachee : %c", keyMap[c+128]);
    }
}
