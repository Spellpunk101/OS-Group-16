CC = gcc
CFLAGS = -Wall

# Executable name
TARGET = chash

# Source files
SRCS = chash.c rwlock.c fhash.c threadcommands.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to build object files
%.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
        rm -f $(OBJS) $(TARGET)
