#include <inttypes.h>
#include "n7OS/time.h"
#include "n7OS/processus.h"

processus_t process_list[NB_PROC];

pid_t fork(const char *name, fnptr function) {
    //trouver un pid libre
    pid_t pid = 0;
    for (int i=0; i<NB_PROC; i++) {
        if (process_list[i].pid == 0) {
            pid = i+1;
            break;
        }
    }
    if (pid == 0) {
        printf("Pas de pid libre\n");
        return -1;
    }
    
    //création du processus
    uint32_t *stack = (uint32_t)malloc(STACK_SIZE);
    process_list[pid-1].pid = pid;
    process_list[pid-1].name = name;
    process_list[pid-1].description = "";
    process_list[pid-1].state = PRET;
    process_list[pid-1].stack = stack;
    process_list[pid-1].stack_top = stack + STACK_SIZE;
}

int exit(){
    free(process_list[getpid()-1].stack);
}

pid_t getpid() {
    for (int i=0; i<NB_PROC; i++) {
        if (process_list[i].state == ELU) {
            return process_list[i].pid;
        }
    }
    return -1;
}

int sleep(uint32_t time) {
    process_list[getpid()-1].state = BLOQUE;
    wakeUpPid(getpid(), getTimer() + time);
}

int unlock(pid_t pid) {
    process_list[pid-1].state = PRET;
}