# Makefile for cpp20_demo project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2 -pthread
INCLUDE = -Iinclude
SRCDIR = src
OBJDIR = build
BINDIR = bin
TARGET = $(BINDIR)/cpp20_demo

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
