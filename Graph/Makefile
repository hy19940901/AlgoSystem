CC = g++
CFLAGS = -std=c++11

SOURCES = ./src/Graph.cpp ./src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Graph_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

../src/%.o: ../src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f *.swo *.swp
