#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h> 
#include "receiver.h"

#define MAX_LEN 1024

static pthread_t s_receiverID;
static struct sockaddr_in s_socket;
static struct sockaddr_in s_sinRemote;
static int s_socket_descriptor;

void* Receiver_thread(void* arg) {
    while(1) {
        // receiving data
        unsigned int sin_len = sizeof(s_sinRemote);
        char bufferRx[MAX_LEN];

        int bytesRx = recvfrom(s_socket_descriptor,
                           bufferRx, MAX_LEN, 0,
                           (struct sockaddr*) &s_sinRemote, &sin_len);

        // adding the null terminating value to the end of the string
        int terminate_index = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        bufferRx[terminate_index] = '\0';
        long remotePort = ntohs(s_sinRemote.sin_port);
        printf("(port %ld) %s\n" , remotePort, bufferRx);
    }

    pthread_exit(NULL);
}

void Receiver_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socket_descriptor) {
    s_socket = *s;
    s_sinRemote = *sinRemote;
    s_socket_descriptor = socket_descriptor;
    pthread_create(&s_receiverID, NULL, Receiver_thread, NULL);
}

void Receiver_shutdown(void) {
    pthread_join(s_receiverID, NULL);
}