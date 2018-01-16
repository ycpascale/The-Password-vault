CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g -lcurses


# note that cpp check reports memory leaks on these files that wouldn't really be leaks when the program was run
# don't blindly believe everything it tells you- check to make sure it is correct.  Usually it is
# but not always.
#run cppcheck

prog: src/vault.c src/func.c src/hashTable.c
	$(CC) $(CFLAGS) src/vault.c src/func.c src/hashTable.c  -Iinclude -o bin/runMe

test: src/testing.c src/func.c
		$(CC) $(CFLAGS) src/testing.c -o bin/testMe

make runs:
		cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
