# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall -g -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Sources and objects
SRCS = $(SRCDIR)/sort_algorithms.cpp $(SRCDIR)/main.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
EXEC = $(BINDIR)/sort_algorithms

# Default target
all: $(EXEC)

# Link final executable
$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .cpp -> .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp include/sort_algorithms.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f *.swo *.swp
