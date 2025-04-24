# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall

# Target executable
TARGET = Lock

# Source files
SRC = ./main.cpp

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target to remove compiled files
clean:
	rm -f $(TARGET)
