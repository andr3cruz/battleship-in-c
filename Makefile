
battleship.o: battleship.c battleship.h
	gcc -c 	battleship.c

battleship: main.o battleship.o
	gcc main.o battleship.o -o battleship

quadtree.o: quadtree.c quadtree.h
	gcc -c 	quadtree.c

quadtree: main.o quadtree.o
	gcc main.o quadtree.o -o quadtree

main.o: main.c battleship.h quadtree.h
	gcc -c main.c

clean:
	rm *.o battleship