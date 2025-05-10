# Makefile for C10K server in pure C with thread pool

CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Iinclude -pthread
SRCDIR = src
OBJDIR = build
BINDIR = bin
TARGET = $(BINDIR)/c10k_c_threadpool

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
