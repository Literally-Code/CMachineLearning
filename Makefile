CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = main.o matrix.o
TARGET = program
BUILD_DIR = build/

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)$(TARGET)

main.o: main.h matrix.h
matrix.o: matrix.h

clean:
	rm -f $(OBJ) $(BUILD_DIR)$(TARGET)

.PHONY: clean
