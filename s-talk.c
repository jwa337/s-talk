#include <stdio.h>
#include <netdb.h>
#include <pthread.h>
#include "modules/receiver.h"
#include "modules/sender.h"
#include "modules/input.h"
#include "modules/output.h"
#include "modules/socket.h"
#include "list/list.h"

int main(int argc, char** argv) {
    // user must specifies their port, the machine and port they wish to connect to
    if (argc != 4) {
        exit(0);
    }

    printf("Starting s-talk session with %s and %s\n", argv[1], argv[3]);

    // condition variables and mutexes for reading input and sending through UDP
    pthread_cond_t inputBufAvail = PTHREAD_COND_INITIALIZER;
    pthread_cond_t inputItemAvail = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t inputMutex = PTHREAD_MUTEX_INITIALIZER;

    // conditon variables and mutexes for receiving from UDP and for printing output
    pthread_cond_t outputBufAvail = PTHREAD_COND_INITIALIZER;
    pthread_cond_t outputItemAvail = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t outputMutex = PTHREAD_MUTEX_INITIALIZER;

    // create input and output lists
    List* inputLst = List_create();  // for storing data that the user types in the keyboard
    List* outputLst = List_create(); // for storing data that received from UDP from another socket

    struct sockaddr_in s;
    struct sockaddr_in sinRemote;
    int socketDescriptor = Socket_init(atoi(argv[1]), atoi(argv[3]), &s, &sinRemote);

    Input_init(inputLst, &inputBufAvail, &inputItemAvail, &inputMutex);
    Sender_init(&sinRemote, socketDescriptor, inputLst, &inputBufAvail, &inputItemAvail, &inputMutex);
    Receiver_init(&sinRemote, socketDescriptor, outputLst, &outputBufAvail, &outputItemAvail, &outputMutex);
    Output_init(outputLst, &outputBufAvail, &outputItemAvail, &outputMutex);

    Input_shutdown();
    Sender_shutdown();
    Receiver_shutdown();
    Output_shutdown();
    Socket_close(socketDescriptor);

    printf("Session Ended...\n");

    return 0;
}