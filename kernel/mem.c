#include <n7OS/mem.h>
#include <stdio.h>
#include <n7OS/kheap.h>

uint32_t *page_table;
uint32_t nombrepages= 0x10000000/PAGE_SIZE;

/**
 * @brief Marque la page allouée
 * 
 * Lorsque la page a été choisie, cette fonction permet de la marquer allouée
 * 
 * @param addr Adresse de la page à allouer
 */

void setPage(uint32_t addr) {
    page_table[addr/0x1000] = 1;
}

/**
 * @brief Désalloue la page
 * 
 * Libère la page allouée.
 * 
 * @param addr Adresse de la page à libérer
 */
void clearPage(uint32_t addr) {
    //free(page_table[addr/0x1000]);
    page_table[addr/0x1000] = 0;
}

/**
 * @brief Fourni la première page libre de la mémoire physique tout en l'allouant
 * 
 * @return uint32_t Adresse de la page sélectionnée
 */
uint32_t findfreePage() {
    uint32_t adresse= 0x0;
    for (int i = 0; i < nombrepages; i++) {
        if (page_table[i] == 0) {
            adresse = i*0x1000;
            setPage(adresse);
            break;
        }
    }
    return adresse;
}

/**
 * @brief Initialise le gestionnaire de mémoire physique
 * 
 */
void init_mem() {
    page_table = (uint32_t *) kmalloc(nombrepages*sizeof(uint32_t));
    for (int i = 0; i < nombrepages; i++) {
        ((uint32_t*) page_table)[i] = 0;
    }
}

/**
 * @brief Affiche l'état de la mémoire physique
 * 
 */
void print_mem() {
    for (int i = 0; i < 1024; i++) {
        if (page_table[i] != 0) {
            printf("Page %d : %x\n", i, page_table[i]);
        }
    }
}