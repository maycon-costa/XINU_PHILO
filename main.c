#include <xinu.h>
#include<stdio.h>
#include<stdlib.h>

#define NUM_FILOSOFOS 5

sid32 mutex;                  
sid32 garfo[NUM_FILOSOFOS];    

void pensar(int id) {
    kprintf("Filósofo %d está pensando.\n", id);
    sleep(1 + rand() % 3); 
}

void comer(int id) {
    kprintf("Filósofo %d está comendo.\n", id);
    sleep(2 + rand() % 2); 
}

void filosofo(int id) {
    while (TRUE) {
        pensar(id);
        wait(mutex); 

        wait(garfo[id]);                  
        wait(garfo[(id + 1) % NUM_FILOSOFOS]); 

        signal(mutex); 

        comer(id); 

        signal(garfo[id]);                  
        signal(garfo[(id + 1) % NUM_FILOSOFOS]); 
    }
}

void main() {
    int i;
    mutex = semcreate(1); 
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        garfo[i] = semcreate(1); 
    }
    for (i = 0; i < NUM_FILOSOFOS; i++) {
        resume(create(filosofo, 1024, 20, "filosofo", 1, i));
    }
    while (TRUE) {
        sleep(10); 
    }
}
