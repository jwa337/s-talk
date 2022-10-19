#include "sender.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>

#define MAX_LEN 1024

static char* message;
static pthread_t s_senderID;
static struct sockaddr_in s_socket;
static struct sockaddr_in s_sinRemote;
static int s_socketDescriptor;
static List* s_lst;

// synchronziation
static pthread_cond_t s_waitingInputCondVar;
static pthread_mutex_t s_inputMutex;

void get_meesage(char* message) {
    size_t ln = -1;
    while (ln <= 0 || ln > MAX_LEN-1) {
        fgets(message, MAX_LEN, stdin);
        ln = strlen(message) - 1;
    }

    if (message[ln] == '\n')
        message[ln] = '\0';
}

void* Sender_thread(void* arg) {
    // sending data
    while (1) {
        //message = malloc(MAX_LEN);
        //get_meesage(message);
        // get message from input list
        List_first(s_lst);
        message = malloc(MAX_LEN);
        message = List_remove(s_lst);
        if () {
            pthread_mutex_lock(&s_inputMutex);
            {
                pthread_cond_wait(&s_waitingInputCondVar, &s_inputMutex);
            }
            pthread_mutex_unlock(&s_inputMutex);
        }

        int sinLen = sizeof(s_sinRemote);
        sendto(s_socketDescriptor,
            message, strlen(message), 0,
        (   struct sockaddr *)&s_sinRemote, sinLen);
    }

    pthread_exit(NULL);
}

void Sender_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socketDescriptor, List* inputLst, pthread_cond_t* inputCondVar, pthread_mutex_t* inputMutex) {
    s_socket = *s;
    s_sinRemote = *sinRemote;
    s_socketDescriptor = socketDescriptor;
    s_waitingInputCondVar = *inputCondVar;
    s_inputMutex = *inputMutex;
    pthread_create(&s_senderID, NULL, Sender_thread, NULL);
}

void Sender_shutdown(void) {
    free(message);
    pthread_join(s_senderID, NULL);
}