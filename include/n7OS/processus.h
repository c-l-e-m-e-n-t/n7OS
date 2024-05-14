#ifndef PROCESSUS_H
#define PROCESSUS_H

#include <inttypes.h>
#include "paging.h"

#define NB_PROC 255
#define STACK_SIZE 1024

typedef uint32_t pid_t;

typedef enum {
    ELU,
    PRET,
    BLOQUE
} processus_state_t;

typedef void* (*fnptr)();

typedef struct {
    pid_t pid;
    char *name;
    char *description;
    processus_state_t state;
    fnptr function;
    uint32_t *stack;
    uint32_t regs[5];
} processus_t;

pid_t fork(const char *name, fnptr function);

int exit();

pid_t getpid();

int sleep(uint32_t time);

int unlock(pid_t pid);

void creer_processus(const char *name, fnptr function);

void schedule();

#endif