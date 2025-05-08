CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Iinclude
LDFLAGS = -lboost_system -lpthread

TARGET = c10k_cpp_threadpool
SRCDIR = src
INCDIR = include

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(SRCDIR)/*.o
