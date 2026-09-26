CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic 
TESTFILE=hash_table_iterator_tests

all: hash_table_iterator_tests
	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

hash_table_iterator_tests: hash_table_iterator_tests.c hash_table_iterator.o hash_table.o
	$(CC) $(FLAGS) -lcunit $^ -o $@

hash_table_iterator.o: hash_table_iterator.c hash_table_iterator.h hash_table.o
	$(CC) $(FLAGS) -c $< -o $@

hash_table_tests: hash_table_tests.c hash_table.o
	$(CC) $(FLAGS) -lcunit $^ -o $@

hash_table.o: hash_table.c hash_table.h hash_table_structs.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests

test:
	./$(TESTFILE)

memtest:
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
