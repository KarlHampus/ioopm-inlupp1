CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=linked_list_tests

all: hash_table_iterator_tests freq_count hash_table_tests linked_list_tests
#	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

linked_list_tests: linked_list_tests.c linked_list.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

linked_list.o: linked_list.c linked_list.h
	$(CC) $(FLAGS) -c $< -o $@

freq_count: freq_count.c hash_table.o hash_table_iterator.o
	$(CC) $(FLAGS) $^ -o $@

hash_table_iterator_tests: hash_table_iterator_tests.c hash_table_iterator.o hash_table.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

hash_table_iterator.o: hash_table_iterator.c hash_table_iterator.h hash_table.o
	$(CC) $(FLAGS) -c $< -o $@

hash_table_tests: hash_table_tests.c hash_table.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

hash_table.o: hash_table.c hash_table.h hash_table_structs.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests linked_list_tests freq_count
	rm -f *.gcda *.gcno *.gcov

test: hash_table_tests hash_table_iterator_tests linked_list_tests
	./$(TESTFILE)

memtest: $(TESTFILE)
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
