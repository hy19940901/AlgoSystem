CC = g++
CFLAGS = -std=c++11

SOURCES = ./src/LinkedList.cpp ./src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = LinkedList_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f *.swo *.swp
