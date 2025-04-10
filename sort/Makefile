CC = g++
CFLAGS = -std=c++20 -Wall -g

SRCS = ./src/SortingAlgorithms.cpp ./src/main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = sorting_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp SortingAlgorithms.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp
