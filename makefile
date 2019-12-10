all: main.o shellfunc.o
	gcc -o dummy main.o shellfunc.o

shellfunc.o: shellfunc.c funcheaders.h
	gcc -c shellfunc.c

main.o: main.c funcheaders.h
	gcc -c main.c

run:
	./dummy

clean:
	rm *.o
	rm *~
