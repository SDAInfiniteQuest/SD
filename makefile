CFLAGS = -Wall -g -O0
#OBJECTS = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
#OBJECTS_DIR = $(patsubst src/%.c, objets/%.o, $(wildcard src/*.c))
CC = gcc
LIB=-lm -lSDL
LIB_PATH=/usr/lib/SDL
INC_PATH = include
SRC_PATH = src
OBJ_PATH = objets
BIN_PATH = bin
VPATH = src:include:objets:bin

ALL: main server client

server: server.o
	gcc $(OBJECT) -o $@ $(OBJ_PATH)/server.o -lm
	mv $@ bin/.
	
client: client.o
	gcc $(OBJECT) -o $@ $(OBJ_PATH)/client.o -lm
	mv $@ bin/.

main :maintest.o adn.o grid.o genetic.o quicksort.o display.o 
	gcc $(CFLAGS) -o $@ $(OBJ_PATH)/adn.o $(OBJ_PATH)/grid.o $(OBJ_PATH)/display.o $(OBJ_PATH)/quicksort.o $(OBJ_PATH)/genetic.o $(OBJ_PATH)/maintest.o  $(LIB)
	mv $@ bin/.

maintest.o: maintest.c adn.h genetic.h display.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@ -I $(LIB_PATH) $(LIB)
	mv $@ objets/.

adn.o: adn.c adn.h 
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

genetic.o: genetic.c genetic.h adn.h grid.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

grid.o: grid.c grid.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

server.o: server.c include.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

client.o: client.c include.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@
	mv $@ objets/.

display.o: display.c display.h
	$(CC) $(CFLAGS)  -c $< -I $(INC_PATH) -o $@ $(LIB)
	mv $@ objets/.


#%.o : %.c
#	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)
#	mv $@ objets/.


test:
	make grid.o
	make main.o
	gcc $(CFLAGS) -o bin/exec objets/*.o -lm

clean : 
	rm $(OBJ_PATH)/*.o $(BIN_PATH)/main 
	rm *~ $(INC_PATH)/*~ $(SRC_PATH)/*~
