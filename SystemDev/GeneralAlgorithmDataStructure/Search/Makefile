# Compiler settings
CC = g++
CFLAGS = -std=c++20 -Wall -g -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source and object files
SRCS = $(SRCDIR)/Search.cpp $(SRCDIR)/main.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
EXEC = $(BINDIR)/searching_program

# Build all
all: $(EXEC)

# Link
$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile each .cpp into obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f *.swo *.swp
