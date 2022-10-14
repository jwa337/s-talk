#include <stdio.h>
#include "modules/receiver.h"
#include "modules/sender.h"
#include "modules/input.h"
#include "modules/output.h"

int main(int argc, char** argv) {
    printf("Starting s-talk session with ... ...\n");

    Receiver_init();

    char x;
    scanf("%c", &x);

    if (x == '!') {
        Receiver_shutdown();
    }

    return 0;
}