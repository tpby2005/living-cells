CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lraylib -lm

living-cells: main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f living-cells

install: living-cells
	cp living-cells /usr/local/bin

all: living-cells