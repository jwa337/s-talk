CFLAGS = -IC -g -std=c99 -Wall -Werror
CLIBS = -lpthread

all: s-talk

s-talk:
	gcc s-talk.c modules/input.c modules/output.c modules/receiver.c modules/sender.c modules/socket.c list/list.c $(CFLAGS) $(CLIBS) -o $@

clean:
	rm -rf s-talk