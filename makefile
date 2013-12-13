CFLAGS = -Wall -g
OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = gcc
INC_PATH = include
SRC_PATH = src
OBJ_PATH = objets
BIN_PATH = bin
VPATH = src:include:objets:bin

all : main

main : $(OBJECTS) 
	gcc $(CFLAGS) -o $@ $(OBJECTS_DIR)
	mv $@ bin/.

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I $(INC_PATH)
	mv $@ objets/.

test:
	make grid.o
	make main.o
	gcc $(CFLAGS) -o bin/exec objets/*.o -lm

clean : 
	rm $(OBJ_PATH)/*.o $(BIN_PATH)/main 
	rm *~ $(INC_PATH)/*~ $(SRC_PATH)/*~
