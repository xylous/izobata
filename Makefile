CC 			?= gcc
CFLAGS 		= -Wall -Wextra -Wpedantic -O3

LIB_NAME 	= izobata.o
VPATH 		= src:
C_SRC_FILES = $(shell ls -I "*.h" src)
OBJECTS  	= $(C_SRC_FILES:.c=.o)
LD_FLAGS 	= -lncurses

all:

main: examples/main.c
	$(CC) $(CFLAGS) -c $< $(LD_FLAGS) -L. -lizobata

izobata.a: $(OBJECTS)
	ar -cvq libizobata.a $(OBJECTS)
	rm $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LD_FLAGS)

clean:
	rm -f $(BIN_NAME) $(OBJECTS)
