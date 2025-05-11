# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -fPIC -Iinclude
LDFLAGS = -llog4cxx

# Determine OS and RPATH
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    LIB_EXT = dylib
    RPATH = @loader_path/
else ifeq ($(UNAME_S), Linux)
    LIB_EXT = so
    RPATH = \$$ORIGIN
endif

# Directories and names
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
LIB_NAME = libstreamprovider.$(LIB_EXT)
LIB_FULL_PATH = $(BIN_DIR)/$(LIB_NAME)
SERVER_BIN = $(BIN_DIR)/stream_server

# Source files
LIB_SRCS = $(SRC_DIR)/stream_provider.cpp \
           $(SRC_DIR)/stream_provider_internal.cpp \
           $(SRC_DIR)/log_config.cpp

SERVER_SRCS = $(SRC_DIR)/stream_server.cpp

# Object files
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(LIB_SRCS))

# Default target
all: $(LIB_FULL_PATH) $(SERVER_BIN)

# Compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build shared library
$(LIB_FULL_PATH): $(LIB_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -shared -o $@ $^

# Build server executable
$(SERVER_BIN): $(SERVER_SRCS) $(LIB_FULL_PATH)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SERVER_SRCS) -L$(BIN_DIR) -lstreamprovider -Wl,-rpath,$(RPATH) $(LDFLAGS)

# Run server
run: $(SERVER_BIN)
	./$(SERVER_BIN)

# Clean build
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) ./logs

.PHONY: all clean run
