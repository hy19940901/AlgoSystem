# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = log_parser

# Source files
SRC = ./src/main.cpp

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target to remove compiled files
clean:
	rm -f $(TARGET)
