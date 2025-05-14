CC = g++
CFLAGS = -std=c++20 -Wall -g

SRCS = math_number_theory.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = math_number_theory

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp