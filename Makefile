
all: bd.c
	gcc -o bd bd.c
	strip bd

clean:
	rm -f *.o *.core a.out bd
