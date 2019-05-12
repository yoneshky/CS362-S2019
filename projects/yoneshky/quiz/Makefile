CFLAGS= -Wall -fpic -coverage -lm -std=c99


testMeResults: 
	gcc -c -g testme.c $(CFLAGS)
	./testMeResults
	gcov testme.c -b

clean:
	rm -f *.o testMeResults *.gcov *.gcda *.gcno *.so *.out
