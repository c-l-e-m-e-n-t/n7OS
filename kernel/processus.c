#include <inttypes.h>
#include "n7OS/time.h"
#include "n7OS/processus.h"
#include <n7OS/cpu.h>

processus_t process_list[NB_PROC];
int compteur, nb_processus;
int current_priorite = 0;

void init_processus() {
    for (int i=0; i<NB_PROC; i++) {
        process_list[i].pid = 0;
    }
    compteur = 0;
    nb_processus = 0;
}

pid_t fork(const char *name, fnptr function) {
    //trouver un pid libre
    pid_t pid = 0;
    for (int i=0; i<NB_PROC; i++) {
        if (process_list[i].pid == 0) {
            pid = i+1;
            nb_processus ++;
            break;
        }
    }
    if (pid == 0) {
        printf("Pas de pid libre\n");
        return -1;
    }
    
    //création du processus dans une page libre
    process_list[pid-1].pid = pid;
    process_list[pid-1].name = name;
    process_list[pid-1].description = "";
    process_list[pid-1].state = PRET;
    process_list[pid-1].function = function;
    process_list[pid-1].regs[0] = 0;
    process_list[pid-1].regs[1] =  process_list[pid-1].stack + STACK_SIZE - 1;
    process_list[pid-1].regs[2] = 0;
    process_list[pid-1].regs[3] = 0;
    process_list[pid-1].regs[4] = 0;
    process_list[pid-1].stack[STACK_SIZE-1] = (uint32_t)function;
    process_list[pid-1].priorite = 1;
    return pid-1;
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

void creer_processus(const char *name, fnptr function, uint32_t priorite) {
    pid_t pid = fork(name, function);
    process_list[pid].priorite = priorite;
    printf("pid %d\n", pid);
    if (pid == -1) {
        return;
    }
}

void set_priorite(pid_t pid, uint32_t priorite) {
    process_list[pid].priorite = priorite;
}

void schedule() {
    static int current_pid = 0;  // L'ID du processus actuellement en cours d'exécution
    if (current_priorite == 0){
        //clear la console 
        console_clear();

        // Si le processus actuel est terminé, passer au suivant
        while (process_list[current_pid].state == BLOQUE) {
            current_pid = (current_pid + 1) % nb_processus;  // Passer au processus suivant
        }
        process_list[(current_pid+nb_processus-1)%nb_processus].state = PRET;
        process_list[current_pid].state = ELU;
        current_priorite = process_list[current_pid].priorite;
        printf("priorite %d\n", current_priorite);

        // Passer au processus suivant pour la prochaine fois que schedule() est appelé
        current_pid = (current_pid + 1) % nb_processus;

        printf("Switching from %s to %s\n", process_list[(current_pid+nb_processus-2)%nb_processus].name, process_list[(current_pid+nb_processus-1)%nb_processus].name);
        printf("Switching from %x to %x\n", process_list[(current_pid+nb_processus-2)%nb_processus].regs[1], process_list[(current_pid+nb_processus-1)%nb_processus].regs[1]);
        sti();
        //context switch
        ctx_sw(process_list[(current_pid+nb_processus-2)%nb_processus].regs, process_list[(current_pid+nb_processus-1)%nb_processus].regs);
    } else {
        current_priorite -- ;
    }
    
}