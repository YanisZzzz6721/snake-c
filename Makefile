CC := clang
CFLAGS := -Wall -Wextra -Wpedantic -O2 -Iinclude
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)
LDFLAGS := $(SDL_LIBS)

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
BIN := snake

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

run: all
	./$(BIN)

.PHONY: all clean run
