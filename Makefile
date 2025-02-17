SRC_DIR = ./source
BUILD_DIR = ./build

CC = gcc
CFLAGS_COMMON = -std=c11 -Wall -Wextra -fanalyzer -Wshadow -Wpedantic -Wconversion
EXE = gargvm

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

CFLAGS = $(CFLAGS_COMMON)
DEBUG_FLAGS = -ggdb -Og -DDEBUG
RELEASE_FLAGS = -Werror -O2 -DNDEBUG

all: debug

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXE): $(OBJ) | $(BUILD_DIR)
	$(CC) $(OBJ) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR)/$(EXE)

release: CFLAGS += $(RELEASE_FLAGS)
release: $(BUILD_DIR)/$(EXE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all debug release clean
