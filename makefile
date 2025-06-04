CC = gcc
CFLGAS = -Wextra -Wall
EXEC = build/a

SRCS = $(wildcard src/*.c)

all:
	$(CC) $(CFLGAS) $(SRCS) -o $(EXEC)