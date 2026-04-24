CC = gcc
INCLUDE_PATH = include
CFLAGS = -Wall -Wextra -O2 -I$(INCLUDE_PATH)
LIBS = -lm
TARGET = program
BUILD_DIR = build
SRC_DIR = src
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/ann.o $(BUILD_DIR)/actvfn.o

GDB_DIR = gdb
DEBUG_CFLAGS = -Wall -Wextra -g -O0 -I$(INCLUDE_PATH)
DEBUG_LIBS = -lm
DEBUG_OBJ = $(GDB_DIR)/main.o $(GDB_DIR)/matrix.o $(GDB_DIR)/ann.o $(GDB_DIR)/actvfn.o

$(BUILD_DIR)/$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GDB_DIR)/$(TARGET): $(DEBUG_OBJ) | $(GDB_DIR)
	$(CC) $(DEBUG_CFLAGS) $(DEBUG_OBJ) -o $(GDB_DIR)/$(TARGET) $(DEBUG_LIBS)

$(GDB_DIR)/%.o: $(SRC_DIR)/%.c | $(GDB_DIR)
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@ 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(GDB_DIR):
	mkdir -p $(GDB_DIR)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_PATH)/matrix.h $(INCLUDE_PATH)/ann.h $(INCLUDE_PATH)/actvfn.h
$(BUILD_DIR)/matrix.o: $(SRC_DIR)/matrix.c $(INCLUDE_PATH)/matrix.h
$(BUILD_DIR)/ann.o: $(SRC_DIR)/ann.c $(INCLUDE_PATH)/ann.h
$(BUILD_DIR)/actvfn.o: $(SRC_DIR)/actvfn.c $(INCLUDE_PATH)/actvfn.h

$(GDB_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_PATH)/matrix.h $(INCLUDE_PATH)/ann.h $(INCLUDE_PATH)/actvfn.h
$(GDB_DIR)/matrix.o: $(SRC_DIR)/matrix.c $(INCLUDE_PATH)/matrix.h
$(GDB_DIR)/ann.o: $(SRC_DIR)/ann.c $(INCLUDE_PATH)/ann.h
$(GDB_DIR)/actvfn.o: $(SRC_DIR)/actvfn.c $(INCLUDE_PATH)/actvfn.h

debug: $(GDB_DIR)/$(TARGET)

clean:
	rm -f $(OBJ) $(BUILD_DIR)/$(TARGET)
	rm -f $(DEBUG_OBJ) $(DEBUG_DIR)/$(TARGET)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

.PHONY: clean run debug
