CC=gcc
CFLAGS=-Iinclude -O2 -Wall -pthread
SRCS=src/main.c src/server.c src/threadpool.c src/utils.c
OBJS=$(SRCS:.c=.o)
TARGET=c10k_c_threadpool

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET) src/*.o