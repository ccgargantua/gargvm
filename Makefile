CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = gargvm
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/gargvm

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: $(EXECUTABLE)

debug: CFLAGS += -DDEBUG -g
debug: all
release: CFLAGS += -O3 -Werror
release: all

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean debug release
