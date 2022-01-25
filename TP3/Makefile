all: test_graphe

test_graphe: test_graphe.o graphe.o io_graphe.o
	gcc -o test_graphe test_graphe.o graphe.o io_graphe.o

graphe.o: graphe.c graphe.h
	gcc -Wall -c graphe.c

io_graphe.o: io_graphe.c graphe.h
	gcc -Wall -c io_graphe.c


test_graphe.o: test_graphe.c graphe.h
	gcc -Wall -c test_graphe.c

clean:
	rm -f *.o test_graphe  *~ data/*~
