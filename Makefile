args = -std=c99 -Wall -lm -g  
#-J5 -O3
dir = ./src/
CC =   gcc
all:
	$(CC) $(args) -c  $(dir)*.c
	$(CC) $(args) *.o  main.c -o Simplex
clean:
	rm ./*.o
	rm ./Simplex
