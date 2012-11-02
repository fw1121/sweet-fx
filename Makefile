# http://www.gnu.org/software/autoconf/manual/make/Wildcard-Function.html
# http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# http://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html#Catalogue-of-Rules
# Compiling C programs
# n.o is made automatically from n.c with a command of the form $(CC) -c $(CPPFLAGS) $(CFLAGS)'. 	

# get the dir this makefile is in
TOP ?= $(shell pwd)

# compiler settings
CC=gcc
OPTIMIZE=-O3
CFLAGS=-Wall -std=c99 -pedantic -ggdb $(OPTIMIZE) $(shell pkg-config --cflags glib-2.0)

# tool name
BIN=fx
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm $(shell pkg-config --libs glib-2.0)

clean:
	$(RM) -f $(BIN) $(wildcard *.o) $(wildcard *~)
