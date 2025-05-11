# === Compiler settings ===
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -fPIC -Iinclude

# === Platform detection ===
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)  # macOS
BOOST_SUFFIX = -mt
BOOST_ROOT = /opt/homebrew/opt/boost
CXXFLAGS += -I$(BOOST_ROOT)/include
LDFLAGS += -L$(BOOST_ROOT)/lib
else  # Assume Ubuntu / Linux
BOOST_SUFFIX =
LDFLAGS +=
endif

# === Boost libraries (auto-suffixed) ===
BOOST_LIBS = \
    -lboost_system$(BOOST_SUFFIX) \
    -lboost_thread$(BOOST_SUFFIX) \
    -lboost_chrono$(BOOST_SUFFIX) \
    -lboost_filesystem$(BOOST_SUFFIX) \
    -lboost_program_options$(BOOST_SUFFIX) \
    -lboost_serialization$(BOOST_SUFFIX) \
    -lboost_coroutine$(BOOST_SUFFIX) \
    -lboost_context$(BOOST_SUFFIX)

# === Directories ===
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
LIBDIR = lib

# === Files ===
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/boost_core_examples.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
EXEC = $(BINDIR)/boost_core_examples
SHARED_LIB = $(LIBDIR)/libboostexample.so

# === Default target ===
all: $(EXEC) $(SHARED_LIB)

# === Build executable ===
$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(BOOST_LIBS)

# === Build shared library ===
$(SHARED_LIB): $(OBJS)
	@mkdir -p $(LIBDIR)
	$(CXX) -shared -fPIC $(OBJS) -o $@ $(LDFLAGS) $(BOOST_LIBS)

# === Compile rule ===
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Clean ===
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR)
	rm -f *.swo *.swp
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR) example_dir
