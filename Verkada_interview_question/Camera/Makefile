# Compiler and flags
CC = g++
CFLAGS = -std=c++20

# Source and object files
SOURCES = ./src/Camera.cpp ./src/MultiCameraProcessor.cpp ./src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Camera_program

# Default target
all: $(EXECUTABLE)

# Linking the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Compiling each .cpp file into .o file
./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f *.swo *.swp
