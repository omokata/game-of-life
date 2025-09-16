CC = gcc
CFLAGS = -Wall -Wextra
CLIBS = -lraylib

TARGET = gol
SRCS = main.c

.PHONY: all run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
