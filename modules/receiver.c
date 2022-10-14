#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h> 
#include "receiver.h"

#define MAX_LEN 1024

static int s_port;
static pthread_t s_receiverID;
static struct sockaddr_in s_socket;
static int s_socket_descriptor;

void* Receiver_thread(void* arg) {
    // initializing the socket
    memset(&s_socket, 0, sizeof(s_socket)); // clearing out garbage values

    s_socket.sin_family = AF_INET;
    s_socket.sin_addr.s_addr = htonl(INADDR_ANY);
    s_socket.sin_port = htons(s_port);

    int s_socketDescriptor = socket(PF_INET  , SOCK_DGRAM, 0);
    bind(s_socketDescriptor, (struct sockaddr*) &s_socket, sizeof(struct sockaddr_in));

    while(1) {
        // receiving data
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char bufferRx[MAX_LEN];

        int bytesRx = recvfrom(s_socketDescriptor,
                           bufferRx, MAX_LEN, 0,
                           (struct sockaddr*)&sinRemote, &sin_len);

        // adding the null terminating value to the end of the string
        int terminate_index = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        bufferRx[terminate_index] = '\0';
        long remotePort = ntohs(sinRemote.sin_port);
        printf("(Port%ld) %s  ", remotePort, bufferRx);
    }

    return NULL;
}

void Receiver_init(struct sockaddr_in* s, int socket_descriptor) {
    s_socket = *s;
    s_socket_descriptor = socket_descriptor;
    pthread_create(&s_receiverID, NULL, Receiver_thread, NULL);
}

void Receiver_shutdown(void) {
    pthread_join(s_receiverID, NULL);
}