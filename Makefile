CC = gcc
CFLAGS = -Wall -Werror 

SRC = $(wildcard *.c)
OUT = $(SRC:%.c=%)
SRIPTS = $(wildcard *.sh)

SRC = philosophes.c #producerConsumer.c

all: $(OUT) $(SRIPTS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -f $(OUT)

.PHONY: clean
