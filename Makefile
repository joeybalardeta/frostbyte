.DEFAULT_GOAL:=all

SRC=src/
OBJ=obj/
BIN=bin/

CC=gcc
CFLAGS=-Wall -std=c11
COMPILE=$(CC) $(CFLAGS)
OBJS:=$(patsubst $(SRC)%.c, $(OBJ)%.o, $(wildcard $(SRC)*.c))

init:
	mkdir -p obj bin

$(OBJ)%.o: $(SRC)%.c
	$(COMPILE) -c $< -o $@

all: init $(OBJS)
	$(COMPILE) $(OBJS) -o $(BIN)frostbyte

clean_obj:
	rm -f $(OBJ)*.o

clean:
	rm -f $(OBJ)*.o $(BIN)frostbyte
