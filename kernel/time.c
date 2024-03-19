#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <n7OS/time.h>
#include <n7OS/console.h>

uint32_t time = 0;
uint32_t h, m, s;

//initialisation du timer d'1 KHz
void timer1kHz() {
    uint32_t freq = 1190000/1000;
    outb(freq&0xFF, 0x40);
    outb((freq>>8)&0xFF, 0x40);
    time = 0;
}

void init_timer(uint32_t freq) {
    uint32_t real_freq = 1190000/freq;
    outb(real_freq&0xFF, 0x40);
}

void avtiver_timer() {
    outb(inb(0x21)&0xfe, 0x21);
}

void desactiver_timer() {
    outb(inb(0x21)|0x01, 0x21);
}

void affichage_time() {
    set_cursor2(0,72);
    if (s<10)
        if(m<10)
            if (h<10)
                printf("0%d:0%d:0%d\n", h, m, s);
            else
                printf("%d:0%d:0%d\n", h, m, s);
        else
            if (h<10)
                printf("0%d:%d:0%d\n", h, m, s);
            else
                printf("%d:%d:0%d\n", h, m, s);
    else
        if(m<10)
            if (h<10)
                printf("0%d:0%d:%d\n", h, m, s);
            else
                printf("%d:0%d:%d\n", h, m, s);
        else
            if (h<10)
                printf("0%d:%d:%d\n", h, m, s);
            else
                printf("%d:%d:%d\n", h, m, s);
}

//refresh de l'affichage de l'horloge
void update_horloge() {
    s = (time/1000)%60;
    m = ((time/1000)%3600)/60;
    h = ((time/1000)/3600)%24;
}
