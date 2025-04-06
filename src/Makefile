CC=gcc
CFLAGS=-g -Wall -O2
TARGET=reruo_shell
SOURCES=main.c reruo_shell.c
OBJECTS=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

auto_clean: $(TARGET)
	rm -f $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all auto_clean clean
