#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "modules/receiver.h"
#include "modules/sender.h"
#include "modules/input.h"
#include "modules/output.h"
#include "modules/socket.h"
//////////////////// adding sinRemote to socket.c so sender and receiver shares a same sinRemote

int main(int argc, char** argv) {
    if (argc != 4) {
        exit(0);
    }

    printf("Starting s-talk session with %s and %s\n", argv[1], argv[3]);

    struct sockaddr_in s;
    struct sockaddr_in sinRemote;
    int socket_desciptor = Socket_init(atoi(argv[1]), atoi(argv[3]), &s, &sinRemote);
    Receiver_init(&s, &sinRemote, socket_desciptor);
    Sender_init(&s, &sinRemote, socket_desciptor);

    char terminated;
    scanf("%c", &terminated);

    Receiver_shutdown();
    Sender_shutdown();
    Socket_close(socket_desciptor);

    return 0;
}