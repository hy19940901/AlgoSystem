# Makefile for c10k_cpp_threadpool with Boost & pthread

CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Iinclude
LDFLAGS = -lboost_system -lpthread

TARGET = bin/c10k_cpp_threadpool
SRCDIR = src
INCDIR = include
OBJDIR = build

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) bin

.PHONY: all clean
