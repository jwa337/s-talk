udpListen:
	gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror network_communication.c -o udpListen -lpthread