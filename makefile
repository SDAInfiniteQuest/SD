CFLAGS = -Wall -g
OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = gcc
INC_PATH = include
SRC_PATH = src
OBJ_PATH = objets
BIN_PATH = bin
VPATH = src:include:objets:bin

all : main server client

server:server.o include.h
	gcc $(OBJECT) -o $@ $(OBJ_PATH)/server.o
	mv $@ bin/.
	
client:client.o include.h
	gcc $(OBJECT) -o $@ $(OBJ_PATH)/client.o
	mv $@ bin/.

main : maintest.o adn.o grid.o genetic.o
	gcc $(CFLAGS) -o $@ $(OBJECTS_DIR)
	mv $@ bin/.

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I$(INC_PATH)
	mv $@ objets/.

clean : 
	rm $(OBJ_PATH)/*.o $(BIN_PATH)/main 
	rm *~ $(INC_PATH)/*~ $(SRC_PATH)/*~
