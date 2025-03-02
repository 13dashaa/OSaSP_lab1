CC = gcc
CFLAGS = -std=c11 -g2 -ggdb -pedantic -W -Wall -Wextra

.SUFFIXES:
.SUFFIXES: .c .o

DEBUG   = ./build/debug
RELEASE = ./build/release
OUT_DIR = $(DEBUG)
vpath %.c src
vpath %.h src
vpath %.o $(OUT_DIR)

ifeq ($(MODE), release)
  CFLAGS = -std=c11 -pedantic -W -Wall -Wextra -Werror
  OUT_DIR = $(RELEASE)
  vpath %.o $(OUT_DIR)
endif

objects =  $(OUT_DIR)/auxiliary_functions.o $(OUT_DIR)/main.o $(OUT_DIR)/walk_directory.o 

prog = $(OUT_DIR)/dirwalk

all: $(prog)

$(prog) : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@


$(OUT_DIR)/%.o : %.c | $(OUT_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	@rm -rf $(DEBUG)/* $(RELEASE)/* dirwalk

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(OUT_DIR)/dirwalk $(args)