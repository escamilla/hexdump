CC=gcc
CFLAGS=-std=gnu99 -Wall -pedantic
BIN=hexdump
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -fv $(BIN) $(OBJS)

