#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "input.h"

#define MAX_LEN 1024
 
static pthread_t s_inputID;
static List* s_Lst;
static char* msg;

void* Input_thread(void* arg) {
    msg = malloc(MAX_LEN);
    size_t length = -1;
    while (length <= 0 || length > MAX_LEN-1) {
        fgets(msg, MAX_LEN, stdin);
        length = strlen(msg) - 1;
    }

    if (msg[length] == '\n') {
        msg[length] = '\0';
    }

    pthread_exit(NULL);
}

void Input_init(List* inputLst) {
    s_Lst = inputLst;
    pthread_create(&s_inputID , NULL, Input_thread, NULL);
}

void Input_shutdown(void) {
    free(msg);
    pthread_join(s_inputID, NULL);
}
