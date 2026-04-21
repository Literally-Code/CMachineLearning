CC = gcc
INCLUDE_PATH = include
CFLAGS = -Wall -Wextra -O2 -I$(INCLUDE_PATH)
TARGET = program
BUILD_DIR = build
SRC_DIR = src
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/matrix.o

$(BUILD_DIR)/$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_PATH)/matrix.h
$(BUILD_DIR)/matrix.o: $(SRC_DIR)/matrix.c $(INCLUDE_PATH)/matrix.h

clean:
	rm -f $(OBJ) $(BUILD_DIR)/$(TARGET)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

.PHONY: clean
