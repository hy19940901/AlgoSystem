# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -I./include

# Source files
SRC = src/main.cpp src/BoostCoreExamples.cpp

# Output executable
TARGET = boost_example

# Boost libraries to link (macOS uses -mt, Ubuntu uses workaround symlinks)
BOOST_LIBS = -lboost_system -lboost_thread-mt -lboost_chrono -lboost_filesystem

# Build target
all: check_boost_symlinks $(TARGET)

# Build executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(BOOST_LIBS)

# Clean up
clean:
	rm -f $(TARGET)
	rm -f *.swo *.swp
	rm -rf ./example_dir

# Ubuntu compatibility: create symlinks if using non -mt Boost libs
check_boost_symlinks:
	@if [ -f /usr/lib/x86_64-linux-gnu/libboost_thread.so ] && [ ! -f /usr/lib/x86_64-linux-gnu/libboost_thread-mt.so ]; then \
		echo "Creating Boost -mt compatibility symlinks for Ubuntu..."; \
		sudo ln -sf /usr/lib/x86_64-linux-gnu/libboost_thread.so /usr/lib/x86_64-linux-gnu/libboost_thread-mt.so; \
		sudo ln -sf /usr/lib/x86_64-linux-gnu/libboost_filesystem.so /usr/lib/x86_64-linux-gnu/libboost_filesystem-mt.so || true; \
		sudo ln -sf /usr/lib/x86_64-linux-gnu/libboost_chrono.so /usr/lib/x86_64-linux-gnu/libboost_chrono-mt.so || true; \
		sudo ln -sf /usr/lib/x86_64-linux-gnu/libboost_system.so /usr/lib/x86_64-linux-gnu/libboost_system-mt.so || true; \
	else \
		echo "Boost symlinks already exist or not needed."; \
	fi
