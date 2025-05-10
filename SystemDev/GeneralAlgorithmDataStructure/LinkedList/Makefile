# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Iinclude -Wall -Wextra

# Paths
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Files
SOURCES = $(SRCDIR)/LinkedList.cpp $(SRCDIR)/main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/LinkedList_program

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

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f *.swo *.swp
