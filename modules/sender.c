#include "sender.h"
#include <stdio.h>
#include <pthread.h>
#include <netdb.h>

static pthread_t s_senderID;
static struct sockaddr_in s_socket;

void* Sender_thread(void* arg) {
    // sending data
    // char message[MAX_LEN];
    // scanf("%s", message);
    // sin_len = sizeof(sinRemote);
    // sendto(s,
    //     message, strlen(message), 0,
    //     (struct sockaddr *)&sinRemote, sin_len);
    return NULL;
}

void Sender_init(struct sockaddr_in* s) {
    s_socket = *s;
    pthread_create(&s_senderID, NULL, Sender_thread, NULL);
}

void Sender_shutdown(void) {
    pthread_join(s_senderID, NULL);
}