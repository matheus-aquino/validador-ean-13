CC      = gcc
CFLAGS  = -Wall -Wextra -g -fsanitize=address
LDFLAGS = -fsanitize=address

programa: validador-ean-13.c
	$(CC) $(CFLAGS) -o $@ validador-ean-13.c $(LDFLAGS)

clean:
	rm -f validador-ean-13
