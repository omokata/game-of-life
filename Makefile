CC = gcc
CFLAGS = -Wall -Wextra -I./include -L.
LDFLAGS = -lm -lraylib

TARGET = gol
SRCS = main.c

.PHONY: all run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
