#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <n7OS/time.h>
#include <n7OS/console.h>
#include <stdio.h>
#include <n7OS/processus.h>
#include <stddef.h>
#include <n7OS/snake.h>

uint32_t time = 0;
uint32_t h, m, s;
typedef struct  {
    pid_t pid;
    uint32_t time;
    struct wakeUpList *next;
}wakeUpList;

wakeUpList *wakeUp = NULL;

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
    uint32_t curseur = get_cursor();
    set_cursor2(0,72);
    printf("%02d:%02d:%02d\n", h, m, s);
    set_cursor(curseur);
}

//refresh de l'affichage de l'horloge
void update_horloge() {
    s = (time/1000)%60;
    m = ((time/1000)%3600)/60;
    h = ((time/1000)/3600)%24;
    affichage_time();
    if (time % 100 == 0) {
        //update_snake();
    }
    if (time % 10 == 0) {
        schedule();
    }
    
    //verifier si un processus doit se reveiller
    wakeUpList *tmp = wakeUp;
    wakeUpList *prev = NULL;
    while (tmp != NULL) {
        if (tmp->time <= time) {
            unlock(tmp->pid);
            if (prev == NULL) {
                wakeUp = tmp->next;
                free(tmp);
                tmp = wakeUp;
            } else {
                prev->next = tmp->next;
                free(tmp);
                tmp = prev->next;
            }
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

int getTimer() {
    return time;
}

void wakeUpPid(pid_t pid, uint32_t time) {
    wakeUpList *new = malloc(sizeof(wakeUpList));
    new->pid = pid;
    new->time = time;
    new->next = wakeUp;
    wakeUp = new;
}
