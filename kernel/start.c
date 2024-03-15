#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>

void kernel_start(void)
{
    init_console();
    setup_base(0 /* la memoire virtuelle n'est pas encore definie */);
    timer1kHz();
    avtiver_timer();

    // lancement des interruptions
    sti();
    // initialisation des interruptions
    init_irq();

    // on ne doit jamais sortir de kernel_start
    while (1) {
        //set le curseur
        //set_cursor2(5, 7);
        // affichage de Hello, World!
        //__asm__ __volatile__("mov␣%0,␣%%cr3"::"r"(&dir ));
        
    }
}
