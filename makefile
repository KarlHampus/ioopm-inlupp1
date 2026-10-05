CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic

all:
	make -C hash_table/ all
	make -C linked_list/ all

clean:
	make -C hash_table/ clean
	make -C linked_list/ clean
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests linked_list_tests freq_count
	rm -f *.gcda *.gcno *.gcov

freq_count:
	make -C hash_table/ freq_count


run_freq_count:
	make -C hash_table/ run_freq_count

test:
	@make -C linked_list/ test
	@make -C hash_table/ test
#	@make clean -s

memtest:
	make -C linked_list/ memtest
	make -C hash_table/ memtest
#	@make clean -s

.PHONY: test clean memtest all run_freq_count
