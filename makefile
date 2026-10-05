CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFOLDER=linked_list

all:
	make -C hash_table/ all
	make -C linked_list/ all

clean:
	make -C hash_table/ clean
	make -C linked_list/ clean
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests linked_list_tests freq_count
	rm -f *.gcda *.gcno *.gcov

test:
	make -C $(TESTFOLDER)/ test
	@make clean -s

memtest:
	make -C $(TESTFOLDER)/ memtest
	@make clean -s

.PHONY: test clean memtest all
