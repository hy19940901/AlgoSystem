# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -fPIC -Iinclude \
           -isystem /usr/include/fmt -isystem /usr/include/spdlog \
           -Wno-array-bounds -Wno-unused-parameter -Wno-sign-compare \
           -Wno-stringop-overflow -Wno-maybe-uninitialized -Wno-restrict

LDFLAGS = -lspdlog -lavformat -lavcodec -lavutil -ltag -lfmt

# Source and build paths
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
OUT = $(BIN_DIR)/media_inspector

# Default target
all: $(OUT)

# Link target
$(OUT): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile each .cpp into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) logs test_utf8.txt

# Run with UTF-8 locale
run: $(OUT)
	LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8 ./$<
