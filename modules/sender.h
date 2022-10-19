#ifndef _UDP_SENDER_H_
#define _UDP_SENDER_H_

#include <netdb.h>
#include <pthread.h>
#include "../list/list.h"

void Sender_init(struct sockaddr_in* s, struct sockaddr_in* sinRemote, int socket_descriptor, List* inputLst, pthread_cond_t* inputCondVar, pthread_mutex_t* inputMutex);

void Sender_shutdown(void);

#endif