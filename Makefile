CC = gcc
CFLAGS = -Wall -Wextra -g
SOURCE_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BINARY_DIR = bin
BINARY_NAME = main

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
BINARY = $(BINARY_DIR)/$(BINARY_NAME)

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJECTS) -o $(BINARY)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

run:
# el @ para que no muestre por pantalla el comando a ejecutar
	@./$(BINARY)

clean: 
	rm -f $(OBJECTS) $(BINARY)

# le dice al make que estos nombres no son archivos
.PHONY: all run clean