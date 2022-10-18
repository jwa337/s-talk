#ifndef _UDP_RECEIVER_H_
#define _UDP_RECEIVER_H_

#include <netdb.h>

void Receiver_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socket_descriptor);

void Receiver_shutdown(void);

#endif