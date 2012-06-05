
all: bd.c
	gcc -o bd bd.c

clean:
	rm -f *.o *.core a.out bd
