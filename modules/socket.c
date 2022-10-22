#include <string.h>
#include <unistd.h>
#include "socket.h"

int Socket_init(int myPort, int connectPort, struct sockaddr_in* s, struct sockaddr_in* sinRemote) {
    // initializing the socket
    memset(s, 0, sizeof(*s)); // clearing out garbage values
    memset(sinRemote, 0 ,sizeof(*sinRemote));

    s->sin_family = AF_INET;
    s->sin_addr.s_addr = htonl(INADDR_ANY);
    s->sin_port = htons(myPort);

    sinRemote->sin_port = htons(connectPort);

    int s_socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    bind(s_socketDescriptor, (struct sockaddr*) s, sizeof(struct sockaddr_in));

    return s_socketDescriptor;
}

void Socket_close(int socketDescriptor) {
    close(socketDescriptor);
}