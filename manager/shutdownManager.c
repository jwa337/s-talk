#include "shutdownManager.h"

static pthread_cond_t* s_shutdownCondVar;
static pthread_mutex_t* s_shutdownMutex;

void WaitForShutDown(pthread_cond_t* shutdownCondVar, pthread_mutex_t* shutdownMutex) {
    s_shutdownCondVar = shutdownCondVar;
    s_shutdownMutex = shutdownMutex;

    pthread_mutex_lock(s_shutdownMutex);
    {
        pthread_cond_wait(s_shutdownCondVar, s_shutdownMutex);
    }
    pthread_mutex_unlock(s_shutdownMutex);
}

void TriggerShutdown() {
    pthread_mutex_lock(s_shutdownMutex);
    {
        pthread_cond_signal(s_shutdownCondVar);
    }
    pthread_mutex_unlock(s_shutdownMutex);
}
