CC = g++
CFLAGS = -std=c++11 -Wall -g

SRCS = ./src/Search.cpp ./src/main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = searching_program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp Search.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp
