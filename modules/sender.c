#include "sender.h"
#include <stdio.h>
#include <pthread.h>
#include <netdb.h>

static pthread_t s_senderID;
static struct sockaddr_in s_socket;
static int s_socket_descriptor;

void* Sender_thread(void* arg) {
    // sending data
    while (1) {
        char message[MAX_LEN];
        scanf("%s", message);
        int sin_len = sizeof(sinRemote);
        sendto(s,
            message, strlen(message), 0,
        (   struct sockaddr *)&sinRemote, sin_len);
    }

    return NULL;
}

void Sender_init(struct sockaddr_in* s, int socket_desciptor) {
    s_socket = *s;
    s_socket_descriptor = socket_desciptor;
    pthread_create(&s_senderID, NULL, Sender_thread, NULL);
}

void Sender_shutdown(void) {
    pthread_join(s_senderID, NULL);
}