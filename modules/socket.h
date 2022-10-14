#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <netdb.h>

struct sockaddr_in* Socket_init(int port, struct sockaddr_in* s);

void Socket_close(struct sockaddr_in s);

#endif