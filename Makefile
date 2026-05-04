CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
LDFLAGS = -lraylib -lm -ldl -lpthread -lX11

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = bin/game

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -rf build bin

re: clean all
