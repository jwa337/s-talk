CFLAGS = -g -std=c99 -Wall -Werror
CLIBS = -lpthread

C_SOURCES := $(wildcard *.c)
C_EXECUTABLE :=$(C_SOURCES:.c=)

all:$(C_EXECUTABLE) $(CPP_EXECUTABLE)

$(C_EXECUTABLE):$(C_SOURCES)
		$(CC) $< $(CFLAGS) $(CLIBS) -o $@

clean:
	rm -rf $(C_EXECUTABLE)