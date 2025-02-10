# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -I./include

# Source files
SRC = src/main.cpp src/BoostCoreExamples.cpp

# Output executable
TARGET = boost_example

# Boost libraries to link
BOOST_LIBS = -lboost_system -lboost_thread-mt -lboost_chrono -lboost_filesystem

# Build target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(BOOST_LIBS)

# Clean up
clean:
	rm -f $(TARGET)
	rm -f *.swo *.swp
	rm -rf ./example_dir