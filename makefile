reversi: reversi.o
	gcc -Wall -O2 -o $@ $^
reversi.o: reversi.c reversi.h
	gcc -c $<
clean:
	rm -f reversi.o reversi