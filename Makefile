
battleship: main.o battleship.o
	gcc main.o battleship.o -o battleship

main.o: main.c battleship.h
	gcc -c main.c

battleship.o: battleship.c battleship.h
	gcc -c 	battleship.c

clean:
	rm *.o battleship