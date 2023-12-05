# Makefile

CC = gcc
CFLAGS = -Wall -Werror 

SRC = $(wildcard *.c)
OUT = $(SRC:%.c=%)

SRC = philosophes.c producerConsumer.c

all: $(OUT) clean

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -f $(OUT)

.PHONY: clean
