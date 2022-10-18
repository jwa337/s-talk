#ifndef _UDP_SENDER_H_
#define _UDP_SENDER_H_

#include <netdb.h>
#include "../list/list.h"

void Sender_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socket_descriptor, List* inputLst);

void Sender_shutdown(void);

#endif