FLAGS=-W -Wall -ansi -pedantic -lm -g
BIN_DIR=./bin/


main: individu.o population.o main.o
	gcc -o main $(BIN_DIR)*.o ${FLAGS}
	
individu.o: individu.c
	gcc -o $(BIN_DIR)individu.o -c individu.c ${FLAGS}
	
population.o: population.c individu.h
	gcc -o $(BIN_DIR)population.o -c population.c ${FLAGS}

main.o: main.c individu.h population.h
	gcc -o $(BIN_DIR)main.o -c main.c ${FLAGS}
clean :
	rm $(BIN_DIR)*.o
	
run : main
	clear
	./main
