CC=cc
CCFLAGS= -g -std=c99 -Wall -Werror

all: socket

%.o: %.c
	$(CC) -c $(CCFLAGS) $<

socket:
	%(CC) -o socket scket.c-Wall -lpthread