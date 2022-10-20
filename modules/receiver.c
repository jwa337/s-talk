#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h> 
#include <unistd.h>
#include "receiver.h"

#define MAX_LEN 256

static pthread_t s_receiverID;
static struct sockaddr_in* s_sinRemote;
static int s_socketDescriptor;
static List* s_lst;

void* Receiver_thread(void* arg) {
    while(1) {
        // receiving data
        unsigned int sinLen = sizeof(*s_sinRemote);
        char bufferRx[MAX_LEN];

        int bytesRx = recvfrom(s_socketDescriptor,
                           bufferRx, MAX_LEN, 0,
                           (struct sockaddr*) s_sinRemote, &sinLen);

        // adding the null terminating value to the end of the string
        int terminateIndex = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        bufferRx[terminateIndex] = '\0';
        long remotePort = ntohs(s_sinRemote->sin_port);
        printf("(port %ld) %s\n" , remotePort, bufferRx);
        //write(s_socketDescriptor, bufferRx, strlen(bufferRx)+1);
    }

    pthread_exit(NULL);
}

void Receiver_init(struct sockaddr_in* sinRemote, int socketDescriptor, List* outputLst) {
    s_sinRemote = sinRemote;
    s_socketDescriptor = socketDescriptor;
    s_lst = outputLst;
    pthread_create(&s_receiverID, NULL, Receiver_thread, NULL);
}

void Receiver_shutdown(void) {
    pthread_join(s_receiverID, NULL);
}