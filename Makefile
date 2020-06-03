QUAD: mainQuad.o quadtree.o battleship.o
	gcc mainQuad.o quadtree.o battleship.o -o battleship

MATRIX: main.o matrix.o battleship.o
	gcc main.o matrix.o battleship.o -o battleship

battleship.o: battleship.c battleship.h
	gcc -c 	battleship.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

quadtree.o: quadtree.c quadtree.h
	gcc -c 	quadtree.c

main.o: main.c battleship.h matrix.h
	gcc -c main.c

mainQuad.o: mainQuad.c battleship.h quadtree.h
	gcc -c mainQuad.c

clean:
	rm *.o battleship