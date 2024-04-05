#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <n7OS/time.h>
#include <n7OS/console.h>
#include <stdio.h>
#include <n7OS/processus.h>
#include <stddef.h>
#include <n7OS/snake.h>
#include <inttypes.h>
#include <n7OS/mem.h>


typedef struct snake_part {
    int x, y;
    struct snake_part *next;
} snake_part;

snake_part *snake_head;
int score = 0;
int direction = 0; // 0: haut, 1: droite, 2: bas, 3: gauche
int fruit_x, fruit_y;

int rand() {
    static uint32_t seed = 0;
    seed = seed * 1664525 + 1013904223;
    return seed;
}

void updateDirection(char c){
    switch (c) {
        case 'z': if (direction != 2) direction = 0; break;
        case 'd': if (direction != 3) direction = 1; break;
        case 's': if (direction != 0) direction = 2; break;
        case 'q': if (direction != 1) direction = 3; break;
    }
}

void new_fruit() {
    fruit_x = rand() % 25;
    fruit_y = rand() % 50;
}

void new_snake() {
    snake_head = malloc(sizeof(snake_part));
    snake_head->x = 25 / 2;
    snake_head->y = 50 / 2;
    snake_head->next = NULL;
    new_fruit();
}

void update_snake() {
    snake_part *new_head = kmalloc(sizeof(snake_part));
    switch (direction) {
        case 0: new_head->x = snake_head->x; new_head->y = snake_head->y - 1; break;
        case 1: new_head->x = snake_head->x + 1; new_head->y = snake_head->y; break;
        case 2: new_head->x = snake_head->x; new_head->y = snake_head->y + 1; break;
        case 3: new_head->x = snake_head->x - 1; new_head->y = snake_head->y; break;
    }
    new_head->next = snake_head;
    snake_head = new_head;
    if (snake_head->x == fruit_x && snake_head->y == fruit_y) {
        score++;
        new_fruit();
    } else {
        snake_part *last = snake_head;
        while (last->next->next) last = last->next;
        free(last->next);
        last->next = NULL;
    }
}

maj_snake(){
    set_cursor2(snake_head->x,snake_head->y);
    printf("O");
    set_cursor2(fruit_x,fruit_y);
    printf("*");
    update_snake();
}

int mainSnake() {
    new_snake();
    maj_snake();
    return 0;
}