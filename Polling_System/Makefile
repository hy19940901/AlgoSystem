# Makefile for Polling System with Boost Libraries
CXX = g++
CXXFLAGS = -std=c++11 -pthread -O2
TARGET = polling_system
BOOST_LIBS = -lboost_system -lboost_thread-mt -lboost_chrono -lboost_filesystem
BOOST_INC = /usr/local/include
BOOST_LIB = /usr/local/lib

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -L$(BOOST_LIB) $(BOOST_LIBS) -o $(TARGET) main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(BOOST_INC) -c main.cpp

clean:
	rm -f $(TARGET) *.o
