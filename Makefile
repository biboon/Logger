CC := x86_64-w64-mingw32-gcc
CC := gcc
TARGET := runner

SOURCES := main.c log.c
OBJECTS := $(SOURCES:.c=.o)

CFLAGS := -g -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE
LIB :=
LDFLAGS :=

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS)
