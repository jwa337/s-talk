#ifndef _UDP_RECEIVER_H_
#define _UDP_RECEIVER_H_

#include <netdb.h>
#include "../list/list.h"

void Receiver_init(struct sockaddr_in* sinRemote, int socketDescriptor, List* outputLst);

void Receiver_shutdown(void);

#endif