CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

bugtest1: bugtest1.c dominion.o rngs.o
	gcc -o bugtest1 bugtest1.c dominion.o rngs.o $(CFLAGS)

bugtest2: bugtest2.c dominion.o rngs.o
	gcc -o bugtest2 bugtest2.c dominion.o rngs.o $(CFLAGS)

bugtest3: bugtest3.c dominion.o rngs.o
	gcc -o bugtest3 bugtest3.c dominion.o rngs.o $(CFLAGS)

bugtest4: bugtest4.c dominion.o rngs.o
	gcc -o bugtest4 bugtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults: bugtest1.c bugtest2.c bugtest3.c bugtest4.c dominion.o rngs.o
	gcc -o bugtest1 bugtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o bugtest2 bugtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o bugtest3 bugtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o bugtest4 bugtest4.c dominion.o rngs.o $(CFLAGS)
	./bugtest1 >> unittestresults.out
	./bugtest2 >> unittestresults.out
	./bugtest3 >> unittestresults.out
	./bugtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out


all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe bugtest*.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
