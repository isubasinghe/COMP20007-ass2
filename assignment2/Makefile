# # # # # # #
# Makefile for assignment 2
#
# created May 2018
# Matt Farrugia <matt.farrugia@unimelb.edu.au>
#

CC     = gcc
CFLAGS = -Wall -std=c99 -lm -O2
# modify the flags here ^
EXE    = a2
OBJ    = main.o list.o spell.o lshtein.o hash.o htable.o gedit.o warray.o
# add any new object files here ^

# top (default) target
all: $(EXE)

# how to link executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# other dependencies
main.o: list.h spell.h
spell.o: spell.h list.h
list.o: list.h
lshtein.o: lshtein.h
gedit.o: gedit.h
hash.o: hash.h
htable.o: htable.h
warray.o: warray.h

# ^ add any new dependencies here (for example if you add new modules)


# phony targets (these targets do not represent actual files)
.PHONY: clean cleanly all CLEAN

# `make clean` to remove all object files
# `make CLEAN` to remove all object and executable files
# `make cleanly` to `make` then immediately remove object files (inefficient)
clean:
	rm -f $(OBJ)
CLEAN: clean
	rm -f $(EXE)
cleanly: all clean
