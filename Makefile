PROJECT_NAME 	:= izobata

CC 			?= gcc
CFLAGS 		:= -Wall -Wextra -Wpedantic -O3
LD_FLAGS 	:= -lncurses -L. -lizobata

VPATH 		:= src:examples

LIB_FILE 	:= lib$(PROJECT_NAME).a
LIB_SRC_FILES 	:= $(shell ls -I "*.h" src)
LIB_OBJECTS 	:= $(LIB_SRC_FILES:.c=.o)

EXAMPLES_BIN_DIR 	:= bin/
EXAMPLES_SRC_FILES 	:= $(shell ls -I "*.h" examples)
EXAMPLES_OBJECTS  	:= $(EXAMPLES_SRC_FILES:.c=.o)
EXAMPLES_BINARIES 	:= $(addprefix $(EXAMPLES_BIN_DIR), $(EXAMPLES_OBJECTS:.o=))

all: library examples

examples: $(EXAMPLES_BINARIES)

$(EXAMPLES_BINARIES): $(EXAMPLES_OBJECTS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $< $(LD_FLAGS)

library: $(LIB_OBJECTS)
	ar -cvq $(LIB_FILE) $(LIB_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LD_FLAGS)

clean:
	rm -f $(LIB_OBJECTS)
	rm -f $(EXAMPLES_OBJECTS)
	rm -rf $(EXAMPLES_BIN_DIR)

fullclean: clean
	rm -f $(LIB_FILE)
