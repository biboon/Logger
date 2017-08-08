CC := gcc
TARGET := runner

SOURCES := main.c log.c
OBJECTS := $(SOURCES:.c=.o)

CFLAGS := -g -std=c99 -pedantic
CFLAGS += -Wall -Wextra
CFLAGS += -Wshadow -Wpointer-arith -Wconversion
CFLAGS += -Wcast-qual -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -D_DEFAULT_SOURCE -D_LOG_LEVEL=LOG_ALL
LIB :=
LDFLAGS :=

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS)
