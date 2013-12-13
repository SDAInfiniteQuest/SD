CFLAGS = -Wall
OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = gcc
INC_PATH = inc
SRC_PATH = src
OBJ_PATH = obj
BIN_PATH = bin
VPATH = src:include:objets:bin

all : main

main : $(OBJECTS) 
	gcc $(CFLAGS) -o $@ $(OBJECTS_DIR)
	mv $@ bin/.

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I $(INC_PATH)
	mv $@ objets/.

clean : 
	rm $(OBJ_PATH)/*.o $(BIN_PATH)/main 
	rm *~ $(INC_PATH)/*~ $(SRC_PATH)/*~
