#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include "modules/receiver.h"
#include "modules/sender.h"
#include "modules/input.h"
#include "modules/output.h"
#include "modules/socket.h"

int main(int argc, char** argv) {
    if (argc < 4) {
        exit(0);
    }

    printf("Starting s-talk session with %s and %s\n", argv[1], argv[3]);

    struct sockaddr_in s;
    Socket_init(atoi(argv[1]), &s);
    Receiver_init(&s);
    Sender_init(&s);

    Receiver_shutdown();
    Sender_shutdown();

    return 0;
}