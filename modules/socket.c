#include <netdb.h>
#include "socket.h"

 struct sockaddr_in* Socket_init(int port, struct sockaddr_in* s) {
    // initializing the socket
    memset(s, 0, sizeof(*s)); // clearing out garbage values

    s->sin_family = AF_INET;
    s->sin_addr.s_addr = htonl(INADDR_ANY);
    s->sin_port = htons(port);

    int s_socketDescriptor = socket(PF_INET  , SOCK_DGRAM, 0);
    bind(s_socketDescriptor, (struct sockaddr*) &s, sizeof(struct sockaddr_in));

    return s;
}

void Socket_close(struct sockaddr_in s) {
    close(s);
}