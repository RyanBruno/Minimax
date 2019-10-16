
FLAGS = -g -Wall

ALL: minimax.o
	gcc $(FLAGS) -o minimax minimax.o
			
minimax.o: minimax.c
	gcc -c $(FLAGS) minimax.c

clean:
	rm *.o
	rm minimax
