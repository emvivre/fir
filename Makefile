all:
	gcc -c -o fir.o fir.c -ansi -Wall -Werror -pedantic -O3

clean:
	rm -f fir.o
