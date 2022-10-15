#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_LEN 1024
#define PORT 22110

int main() {
    printf("STARTING...\n");
    struct sockaddr_in s;
    memset(&s, 0, sizeof(s)); // clearing out garbage values

    s.sin_family = AF_INET;
    s.sin_addr.s_addr = htonl(INADDR_ANY);
    s.sin_port = htons(PORT);

    int s_socketDescriptor = socket(PF_INET  , SOCK_DGRAM, 0);
    bind(s_socketDescriptor, (struct sockaddr*) &s, sizeof(struct sockaddr_in));

    struct sockaddr_in sinRemote;
    unsigned int sin_len = sizeof(sinRemote);

    while(1) {
        // receiving data
        char bufferRx[MAX_LEN];
 
        int bytesRx = recvfrom(s_socketDescriptor,
                           bufferRx, MAX_LEN, 0,
                           (struct sockaddr*)&sinRemote, &sin_len);

        // adding the null terminating value to the end of the string
        int terminate_index = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        bufferRx[terminate_index] = '\0';
        long remotePort = ntohs(sinRemote.sin_port);
        printf("(Port%ld) %s  ", remotePort, bufferRx);
    }

    //close(s_socketDescriptor);
}