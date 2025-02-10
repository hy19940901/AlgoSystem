CC = g++
CFLAGS = -std=c++11 -O2 -I/opt/homebrew/Cellar/ffmpeg/7.1_3/include
LDFLAGS = -L/opt/homebrew/Cellar/ffmpeg/7.1_3/lib -lavcodec -lavformat -lavutil -lswscale -lswresample

SOURCES = ./src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = Ffmpeg_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f *.swo *.swp
