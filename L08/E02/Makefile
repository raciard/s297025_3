OBJS	= es02.o grafo.o ST.o Item.o
SOURCE	= es02.c grafo.c ST.c Item.c
HEADER	= grafo.h ST.h Item.h menu.h
OUT	= es02.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

es02.o: es02.c
	$(CC) $(FLAGS) es02.c 

grafo.o: grafo.c
	$(CC) $(FLAGS) grafo.c 

ST.o: ST.c
	$(CC) $(FLAGS) ST.c 

Item.o: Item.c
	$(CC) $(FLAGS) Item.c 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
