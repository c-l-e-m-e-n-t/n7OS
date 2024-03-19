#include <n7OS/processus.h>
#include <stddef.h>

void init_timer(uint32_t frequence);

void timer1kHz();

void desactiver_timer();

void activer_timer();

void update_horloge();

extern uint32_t time;

int getTimer();

void wakeUpPid(pid_t pid, uint32_t time);

