CC = g++
CFLAGS = -std=c++11 -Wall -g

SRCS = Maze.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = Maze_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp
