# Variables
CXX = g++
CFLAGS = -std=c++11 -O2 -I./include
LDFLAGS = -L/usr/lib64 -lavcodec -lavformat -lavutil

SOURCES = ./src/main.cpp ./src/mp3_info.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Ffmpeg_program

# Default target
all: $(EXECUTABLE)

# Link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

# Compile source files to object files
./src/%.o: ./src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) subtitles.txt
