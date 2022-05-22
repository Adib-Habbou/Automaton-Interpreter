CC = gcc # gnu compiler collection
CF = -Wall -Wextra # warning options

automaton : automaton.o stack.o matrix.o
	$(CC) $(CF) -o $@ $^

automaton.o : automaton.c stack.h matrix.h
	$(CC) $(CF) -o $@ -c $<

stack.o : stack.c
	$(CC) $(CF) -o $@ -c $^

matrix.o : matrix.c
	$(CC) $(CF) -o $@ -c $^

clean : # delete all the object files 
	rm -f *.o
