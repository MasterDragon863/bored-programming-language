CC = cc

ifeq ($(NDEBUG), 1)
CFLAGS = -Wall -Wextra -Werror -std=c89 -pedantic -O3 -Wpedantic
else
CFLAGS = -Wall -Wextra -Werror -std=c89 -pedantic -ggdb -Wpedantic
endif

LINKER_FLAGS = 

SOURCES = $(shell find src -name '*.c')
TARGET = build/main

all: $(TARGET)

$(TARGET): $(SOURCES) | build
	$(CC) $(CFLAGS) $(SOURCES) $(LINKER_FLAGS) -o $(TARGET)

build:
	mkdir build/

run:
	./$(TARGET)

clean:
	rm -rf build/*

.PHONY: all run clean

