#include <stdio.h>
#include <pthread.h>
#include "input.h"
 
static pthread_t s_inputID;

void* Input_thread(void* arg) {
    return NULL;
}

void Input_init(void) {
    pthread_create(&s_inputID , NULL, Input_thread, NULL);
}

void Input_shutdown(void) {
    pthread_join(s_inputID, NULL);
}
