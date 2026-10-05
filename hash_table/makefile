CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=hash_table_tests
DEPENDENCIES=hash_table_iterator.o hash_table.o ../common.o

all: hash_table_iterator_tests freq_count hash_table_tests
#	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@

%_tests: %_tests.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -lcunit

hahs_table.o: ../common.h

hash_table_iterator.o: hash_table.h ../common.h

clean:
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests freq_count
	rm -f *.gcda *.gcno *.gcov

test: $(TESTFILE)
	./$(TESTFILE)

memtest: $(TESTFILE)
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
