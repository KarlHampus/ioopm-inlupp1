CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=linked_list

all:
	make -C hash_table/ all
	make -C linked_list/ all

common.o: common.c common.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make -C hash_table/ clean
	make -C linked_list/ clean
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests linked_list_tests freq_count
	rm -f *.gcda *.gcno *.gcov

test:
	make -C $(TESTFILE)/ test

memtest:
	make -C $(TESTFILE)/ memtest

.PHONY: test clean memtest all
