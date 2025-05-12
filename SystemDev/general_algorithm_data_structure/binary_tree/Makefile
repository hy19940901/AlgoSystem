# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall -Iinclude -g

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Sources and objects
SOURCES = $(SRCDIR)/binary_tree.cpp \
          $(SRCDIR)/main.cpp

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Executable target
EXECUTABLE = $(BINDIR)/binary_tree

# Default rule
all: $(EXECUTABLE)

# Link all objects
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .cpp to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f *.swo *.swp
