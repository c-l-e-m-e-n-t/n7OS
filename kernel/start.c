#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>

void kernel_start(void)
{
    init_console();
    setup_base(0 /* la memoire virtuelle n'est pas encore definie */);

    // lancement des interruptions
    sti();

    // on ne doit jamais sortir de kernel_start
    while (1) {
        //set le curseur
        //set_cursor2(5, 7);
        // affichage de Hello, World!
        printf("Hello, World!\n");
        printf("\tje suis \4clement\n");
        printf("\7je suis un etudiant en informatique\n");
        printf("\8haha !\rje suis en train de faire un systeme d'exploitation\n\n");
        printf("\2\fHaha c'est rigolo");

        // cette fonction arrete le processeur
        hlt();
        
    }
}
