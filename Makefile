
battleship.o: battleship.c battleship.h
	gcc -c 	battleship.c

battleship: mainQuad.o battleship.o
	gcc main.o battleship.o -o battleship

quadtree.o: quadtree.c quadtree.h
	gcc -c 	quadtree.c

quadtree: mainQuad.o quadtree.o
	gcc mainQuad.o quadtree.o -o quadtree

main.o: mainQuad.c battleship.h quadtree.h
	gcc -c mainQuad.c

clean:
	rm *.o battleship