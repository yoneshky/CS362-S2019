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

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g  dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g  dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g  dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g  dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g  dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g  dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g  dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g  dominion.o rngs.o $(CFLAGS)

default: assignment5testresults.out

afivetestresults: dominion.c unittest1.c unittest2.c cardtest1.c cardtest2.c randomtestadventurer.c randomtestcard1.c
	echo "Result for running Assignment 5 tests:" >> assignment5testresults.out
	echo "unittest1.c:" >> assignment5testresults.out
	./unittest1 >> assignment5testresults.out
	gcov unittest1.c -b >> assignment5testresults.out

	echo "unittest2.c:" >> assignment5testresults.out
	./unittest2 >> assignment5testresults.out
	gcov dominion.c -b >> assignment5testresults.out

	echo "cardtest1.c:" >> assignment5testresults.out
	./cardtest1 >> assignment5testresults.out
	gcov dominion.c -b >> assignment5testresults.out

	echo "cardtest2.c:" >> assignment5testresults.out
	./cardtest2 >> assignment5testresults.out
	gcov dominion.c -b >> assignment5testresults.out

	echo "randomtestadventurer.c:" >> assignment5testresults.out
	./randomtestadventurer >> assignment5testresults.out
	gcov randomtestadventurer.c -b >> assignment5testresults.out

	echo "randomtestcard1.c:" >> assignment5testresults.out
	./randomtestcard1 >> assignment5testresults.out
	gcov randomtestcard1.c -b >> assignment5testresults.out

all: playdom player randomtestadventurer randomtestcard1 unittest1 unittest2 cardtest1 cardtest2

clean:
	rm -f *.o playdom.exe playdom player player.exe unittest1 unittest1.exe unittest2 unittest2.exe cardtest1 cardtest1.exe cardtest2 cardtest2.exe randomtestadventurer randomtestadventurer.exe randomtestcard1 randomtestcard1.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
