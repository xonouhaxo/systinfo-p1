# Makefile

CC = gcc
CFLAGS = -Wall -Werror 

SRC = philosophes.c
OBJ = $(SRC:.c=.o)
COMPILE = philosophes

all: $(COMPILE) run clean 

$(COMPILE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: $(COMPILE)
	./$(COMPILE)

clean:
	rm -f $(COMPILE) $(OBJ)

.PHONY: clean
