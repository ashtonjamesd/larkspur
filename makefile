CC = gcc
CFLGAS = -Wextra -Wall
EXEC = build/larkspur

SRCS = $(wildcard src/*.c)

all:
	$(CC) $(CFLGAS) $(SRCS) -o $(EXEC)