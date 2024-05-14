#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>
#include <n7OS/keyboard.h>
#include <n7OS/paging.h>
#include <n7OS/kheap.h>
#include "/home/ccognard/Annee2/S2/Systeme/Projet/n7OS/bin/processus.h"

void kernel_start(void)
{
    init_console();
    kheap_init();
    uint32_t pageDirectory = initialise_paging();
    setup_base(pageDirectory /* la memoire virtuelle n'est pas encore definie */);
    logo();
    
    timer1kHz();
    avtiver_timer();

    // initialisation du clavier
    init_keyboard();
    activer_keyboard();

    // initialisation des interruptions
    init_irq();
    // lancement des interruptions
    sti();

    //initialisation des processus
    creer_processus("idle", idle);
    creer_processus("proc1", processus1);
    
    // on ne doit jamais sortir de kernel_start
    while (1) {

    }
}
