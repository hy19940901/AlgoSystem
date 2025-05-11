# Makefile for generic_thread_pool

CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2 -pthread -Iinclude

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = build
TARGET = $(BIN_DIR)/generic_thread_pool

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
