CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
DEPENDENCIES=hash_table/hash_table_iterator.o hash_table/hash_table.o common.o
FILE=bibeln.txt

all:
	make -C hash_table/ all
	make -C linked_list/ all

clean:
	make -C hash_table/ clean
	make -C linked_list/ clean
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests linked_list_tests freq_count
	rm -f *.gcda *.gcno *.gcov

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@ -pg

hash_table/hash_table.o: common.h

hash_table/hash_table_iterator.o: hash_table/hash_table.h common.h

freq_count: freq_count.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -pg

run_freq_count: freq_count
	./freq_count $(FILE)

gprof_freq_count: freq_count
	make -B freq_count
	./freq_count $(FILE)
	gprof -Q freq_count

test:
	@make -C linked_list/ test
	@make -C hash_table/ test
#	@make clean -s

memtest:
	make -C linked_list/ memtest
	make -C hash_table/ memtest
#	@make clean -s

coverage:
	make -C hash_table/ coverage COVFLAGS="$(COVFLAGS)"
	make -C linked_list/ coverage COVFLAGS="$(COVFLAGS)"

.PHONY: test clean memtest all run_freq_count coverage
