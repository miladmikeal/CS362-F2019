OBJS	= testme.o
SOURCE	= testme.c
HEADER	= 
OUT	= testme
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

testme.o: testme.c
	$(CC) $(FLAGS) testme.c 


clean:
	rm -f $(OBJS) $(OUT)