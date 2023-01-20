OBJS	= es03.o data.o list.o quotazione.o Titolo.o quotazionibst.o
SOURCE	= es03.c data.c list.c quotazione.c Titolo.c quotazionibst.c
HEADER	= data.h list.h quotazione.h Titolo.h quotazionibst.h
OUT	= es03.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

es03.o: es03.c
	$(CC) $(FLAGS) es03.c 

data.o: data.c
	$(CC) $(FLAGS) data.c 

list.o: list.c
	$(CC) $(FLAGS) list.c 

quotazione.o: quotazione.c
	$(CC) $(FLAGS) quotazione.c 

Titolo.o: Titolo.c
	$(CC) $(FLAGS) Titolo.c 

quotazionibst.o: quotazionibst.c
	$(CC) $(FLAGS) quotazionibst.c 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
