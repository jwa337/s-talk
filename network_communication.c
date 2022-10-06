#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_LEN 1024

int main(int argc, char** argv) {
    const int PORT = atoi(argv[1]);

    // initializing the socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // clearing out garbage values

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    int s = socket(PF_INET, SOCK_DGRAM, 0);
    bind(s, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));

    while(1) {
        // receiving data
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char bufferRx(MAX_LEN);

        int bytesRx = recvfrom(s,
                           bufferRx, MAX_LEN, 0,
                           (struct sockaddr *)&sinRemote, % sin_len);

        // adding the null terminating value to the end of the string
        int terminate_index = (bytesRx < MAX_LEN) ? bytesRx : MAX_LEN - 1;
        bufferRx[terminate_index] = '\0';
        printf("%s\n", bufferRx);

        // sending data
        char *message;
        scanf("%s", message);
        sin_len = sizeof(sinRemote);
        sendto(s,
            message, strtlen(message), 0,
            (struct sockaddr *)&sinRemote, sin_len);
    }

    return 0;
}