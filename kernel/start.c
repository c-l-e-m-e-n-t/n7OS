#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>
#include <n7OS/keyboard.h>

void kernel_start(void)
{
    init_console();
    setup_base(0 /* la memoire virtuelle n'est pas encore definie */);
    timer1kHz();
    avtiver_timer();
    logo();
    // initialisation du clavier
    init_keyboard();
    activer_keyboard();
    // lancement des interruptions
    sti();
    // initialisation des interruptions
    init_irq();

    set_cursor2(0, 0);

    
    // on ne doit jamais sortir de kernel_start
    while (1) {

    }
}
