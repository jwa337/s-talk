#include <stdio.h>
#include <pthread.h>
#include "output.h"

static pthread_t s_outputID;

void* Output_thread(void* arg) {
    return NULL; 
}

void Output_init(void) {
     pthread_create(&s_outputID, NULL, Output_thread, NULL);
}

void Output_shutdown(void) {
    pthread_join(s_outputID, NULL);
}