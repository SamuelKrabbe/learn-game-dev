CXX ?= c++
CFLAGS = -Wall -Wextra -std=c++20 -I.
LDFLAGS = -lraylib -lm -ldl -lpthread -lX11

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = bin/game

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) -o $(BIN) $(LDFLAGS)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -rf build bin

re: clean all
