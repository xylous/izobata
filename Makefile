PROJECT_NAME 	:= izobata

CC 			?= gcc
CFLAGS 		:= -Wall -Wextra -Wpedantic -O3
LD_FLAGS 	:= -lncurses -L. -lizobata

VPATH 		:= src:examples:

OBJECTS_DIR := objects

LIB_FILE 	:= lib$(PROJECT_NAME).a
LIB_SRC_FILES 	:= $(shell ls -I "*.h" src)
LIB_OBJECTS 	:= $(addprefix $(OBJECTS_DIR)/, $(LIB_SRC_FILES:.c=.o))

EXAMPLES_BIN_DIR 	:= bin
EXAMPLES_SRC_FILES 	:= $(shell ls -I "*.h" examples)
EXAMPLES_BINARIES 	:= $(addprefix $(EXAMPLES_BIN_DIR)/, $(EXAMPLES_SRC_FILES:.c=))

all: library examples

debug: CFLAGS += -g
debug: all

examples: $(EXAMPLES_BINARIES)

$(EXAMPLES_BIN_DIR)/%: $(OBJECTS_DIR)/%.o
	mkdir -p $(EXAMPLES_BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LD_FLAGS)

library: $(LIB_OBJECTS)
	ar -cvq $(LIB_FILE) $(LIB_OBJECTS)

$(OBJECTS_DIR)/%.o: %.c
	mkdir -p objects
	$(CC) $(CFLAGS) -o $@ -c $< $(LD_FLAGS)

clean:
	rm -rf $(EXAMPLES_BIN_DIR)
	rm -rf $(OBJECTS_DIR)

fullclean: clean
	rm -f $(LIB_FILE)
