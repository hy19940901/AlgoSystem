# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Iinclude -Wall -Wextra

# Source and build directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin
EXECUTABLE = $(BINDIR)/graph

# Source files
SOURCES = $(SRCDIR)/graph.cpp \
          $(SRCDIR)/main.cpp \
          $(SRCDIR)/disjoint_set.cpp

# Object files (replace .cpp with .o and put in obj/)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(EXECUTABLE)

# Link
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each .cpp to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)
