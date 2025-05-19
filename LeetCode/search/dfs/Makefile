CC = g++
CFLAGS = -std=c++20 -Wall -g

SRCS = dfs.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = dfs

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f *.swo *.swp