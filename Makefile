# Compiler
CC=g++
# Compiler flags
CFLAGS=-c -Wall -Wextra -Werror -std=c++11 -O2
# Linker flags
LDFLAGS=
# Include directories
INC_DIR=-Iinclude/
# Source directory
SRC_DIR=src/
# Object directory
OBJ_DIR=build/
# Binary output directory
BIN_DIR=bin/
# Source files
SRCS=$(wildcard $(SRC_DIR)*.cpp)
# Object files
OBJS=$(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
# Binary output file
BIN=$(BIN_DIR)output

all: $(BIN)

$(BIN): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $< -o $@

clean:
	rm $(RM) $(OBJ_DIR)*.o