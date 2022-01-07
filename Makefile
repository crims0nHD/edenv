-include custom.make

CC ?= clang
CFLAGS ?= -g -O0

INCLUDE ?= -I./include

LDFLAGS ?= -pthread

SRC_FILES = $(shell find ./src/ -type f -name "*.c")
SRC_DIRS = $(shell find ./src/ -type d)

OBJ_FILES = $(patsubst %.c, %.o, $(patsubst ./src/%, ./build/obj/%, $(SRC_FILES)))
OBJ_DIRS = $(patsubst ./src/%, ./build/obj/%, $(SRC_DIRS))

BIN_NAME = edenv

.PHONY = build_dirs clean install uninstall help

all: build_dirs build

build: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o ./build/bin/$(BIN_NAME) $(OBJ_FILES)

./build/obj/%.o: ./src/%.c
	echo Building $< ...
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

build_dirs:
	mkdir -p ./build/bin
	mkdir -p ./build/share
	mkdir -p $(OBJ_DIRS)

clean:
	-@rm -r ./build
	echo Cleaning working tree

install:
	echo installing

uninstall:
	echo uninstalling

help:
	echo help goes here
