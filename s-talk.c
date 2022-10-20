#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include "modules/receiver.h"
#include "modules/sender.h"
#include "modules/input.h"
#include "modules/output.h"
#include "modules/socket.h"
#include "list/list.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        exit(0);
    }

    printf("Starting s-talk session with %s and %s\n", argv[1], argv[3]);

    List* inputLst = List_create();
    List* outputLst = List_create();

    // condition variables and mutexes for reading input and sending through UDP
    pthread_cond_t bufAvail = PTHREAD_COND_INITIALIZER;
    pthread_cond_t itemAvail = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t inputMutex = PTHREAD_MUTEX_INITIALIZER;

    // conditon variables and mutexes for receiving from UDP and output


    struct sockaddr_in s;
    struct sockaddr_in sinRemote;
    int socketDescriptor = Socket_init(atoi(argv[1]), atoi(argv[3]), &s, &sinRemote);
    Input_init(inputLst, &bufAvail, &itemAvail, &inputMutex);
    Sender_init(&sinRemote, socketDescriptor, inputLst, &bufAvail, &itemAvail, &inputMutex);
    Receiver_init(&sinRemote, socketDescriptor, outputLst);

    Input_shutdown();
    Sender_shutdown();
    Receiver_shutdown();
    Socket_close(socketDescriptor);

    printf("Session Ended...\n");

    return 0;
}