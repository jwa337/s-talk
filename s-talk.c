#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
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

    struct sockaddr_in s;
    struct sockaddr_in sinRemote;
    int socketDescriptor = Socket_init(atoi(argv[1]), atoi(argv[3]), &s, &sinRemote);
    Receiver_init(&s, &sinRemote, socketDescriptor, outputLst);
    Sender_init(&s, &sinRemote, socketDescriptor, inputLst);
    Input_init(inputLst);

    Receiver_shutdown();
    Sender_shutdown();
    Input_shutdown();
    Socket_close(socketDescriptor);

    printf("Session Ended...\n");

    return 0;
}