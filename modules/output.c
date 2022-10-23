#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "output.h"
#include "../manager/shutdownManager.h"

static pthread_t s_outputID;
static List* s_lst;
static char* msg;

// synchronization
static pthread_cond_t* s_bufAvail;
static pthread_cond_t* s_itemAvail;
static pthread_mutex_t* s_outputMutex;

void* Output_thread(void* arg) {
    while (1) {
        // get message from input list
        if (List_count(s_lst) == 0) {
            pthread_mutex_lock(s_outputMutex);
            {
                pthread_cond_wait(s_itemAvail, s_outputMutex);
            }
            pthread_mutex_unlock(s_outputMutex);
        }

        msg = List_trim(s_lst);
        pthread_mutex_lock(s_outputMutex);
        {
            pthread_cond_signal(s_bufAvail);
        }
        pthread_mutex_unlock(s_outputMutex);

        puts(msg);

        if (msg[0] == '!' && strlen(msg) == 1) {
            TriggerShutdown();
        }
    }
    
    return(NULL);
}

void Output_init(List* inputLst, pthread_cond_t* bufAvail, pthread_cond_t* itemAvail, pthread_mutex_t* outputMutex) {
    s_lst = inputLst;
    s_bufAvail = bufAvail;
    s_itemAvail = itemAvail;
    s_outputMutex = outputMutex;
    pthread_create(&s_outputID, NULL, Output_thread, NULL);
}

void Output_shutdown() {
    pthread_cancel(s_outputID);
    pthread_join(s_outputID, NULL);

    free(msg);
    msg = NULL;
}