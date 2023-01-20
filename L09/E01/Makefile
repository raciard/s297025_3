OBJS	= main.o grafo.o ST.o Item.o
SOURCE	= main.c grafo.c ST.c Item.c
HEADER	= grafo.h ST.h Item.h
OUT	= es01.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

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
