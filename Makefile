SRC := \
	rwlock.c \
        fhash.c \
        threadcommands.c \
        chash.c

OBJ := $(SRC:%.c=%.o)

PRG := chash

.PHONY: all clean

all: $(PRG)

$(PRG): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(PRG)
