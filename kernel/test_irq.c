#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/time.h>

extern void handler_IT();
extern void handler_IT_50();
extern void handler_IT_20();


void init_irq() {
    init_irq_entry(50, handler_IT_50);
    init_irq_entry(32, handler_IT_20);
}

void handler_en_C() {
}

void handler_50() {
    console_putbytes("IT 50\n", 7);
}

void handler_20() {
    time ++;
    outb(0x20, 0x20);
    update_horloge();
}
