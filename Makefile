CC = /usr/bin/gcc
SRCS = $(wildcard *.c)
CFLGS = -Wall -Werror -D_FILE_OFFSET_BITS=64
OBJS = $(SRCS:.c=.o)

all: advent

clean:
	rm -f advent *.o

advent.o:
	$(CC) $(CFLGS) -c -o advent.o advent.c
