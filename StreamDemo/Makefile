# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -I../include  # Use C++11 standard and include header path

# Shared library name and path
LIB_NAME = libstreamprovider.so
LIB_PATH = .

# Source files for the shared library
LIB_SRCS = ./src/stream_provider.cpp ./src/stream_provider_internal.cpp

# Source files for the server executable
SERVER_SRCS = ./src/server.cpp

# Object files for the shared library (automatically generated)
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

# Default target
all: $(LIB_NAME) server

# Compile the shared library
$(LIB_NAME): $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $(LIB_NAME) $(LIB_OBJS)

# Compile the server executable, link the shared library, and set RPATH
server: $(SERVER_SRCS) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o server $(SERVER_SRCS) -L$(LIB_PATH) -lstreamprovider -Wl,-rpath=$(LIB_PATH)

# Compile object files for the shared library
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

# Clean up generated files
clean:
	rm -f server $(LIB_NAME) $(LIB_OBJS)
