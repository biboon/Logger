CC := gcc
TARGET := runner

SOURCES := main.c log.c
OBJECTS := $(SOURCES:.c=.o)

CFLAGS := -g -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE -D_LOG_MIN_TRACE
LIB :=
LDFLAGS :=

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS)
