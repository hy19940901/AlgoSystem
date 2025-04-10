CC = g++
CFLAGS = -std=c++20

SOURCES = ./src/BinaryTree.cpp ./src/BinarySearchTree.cpp ./src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = BinaryTree_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f *.swo *.swp
