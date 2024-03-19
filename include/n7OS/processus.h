#ifndef PROCESSUS_H
#define PROCESSUS_H

#include <inttypes.h>
#include "paging.h"

#define NB_PROC 10
#define STACK_SIZE 1024

typedef uint32_t pid_t;

typedef enum {
    ELU,
    PRET,
    BLOQUE
} processus_state_t;


typedef struct {
    pid_t pid;
    char *name;
    char *description;
    processus_state_t state;
    uint32_t *stack;
    uint32_t *stack_top;
} processus_t;

typedef void* (*fnptr)();

pid_t fork(const char *name, fnptr function);

int exit();

pid_t getpid();

int sleep(uint32_t time);

int unlock(pid_t pid);

#endif