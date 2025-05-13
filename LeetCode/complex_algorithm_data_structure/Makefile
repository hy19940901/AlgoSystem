CC = g++
CFLAGS = -std=c++20 -Wall -g

SRCS = ./complex_algorithm_data_structure.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = complex_algorithm_data_structure

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp