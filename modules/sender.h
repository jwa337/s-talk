#ifndef _UDP_SENDER_H_
#define _UDP_SENDER_H_

#include <netdb.h>

void Sender_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socket_descriptor);

void Sender_shutdown(void);

#endif