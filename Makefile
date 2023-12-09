CC = gcc
CFLAGS = -Wall -Werror 

SRC = $(wildcard *.c)
OUT = $(SRC:%.c=%)
SRIPTS = $(wildcard *.sh)
CSV = $(wildcard *.csv)

SRC = philosophes.c test-and-set.c
all: $(OUT) $(SRIPTS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -f $(OUT) $(CSV)

.PHONY: clean
