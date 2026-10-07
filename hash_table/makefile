CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
DEPENDENCIES=hash_table_iterator.o hash_table.o ../common.o

all: hash_table_iterator_tests freq_count hash_table_tests
#	./$(TESTFILE)

freq_count: freq_count.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -lcunit

run_freq_count: freq_count
	./freq_count ../10k-words.txt

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@

%_tests: %_tests.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -lcunit

hash_table.o: ../common.h

hash_table_iterator.o: hash_table.h ../common.h

clean:
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests freq_count
	rm -f *.gcda *.gcno *.gcov

TEST_SOURCES := $(wildcard *_tests.c)
TESTS := $(TEST_SOURCES:.c=)
test: $(TESTS)
	@for test in $(TESTS); do ./$$test; done

memtest: $(TESTS)
	@for test in $(TESTS); do valgrind --leak-check=full ./$$test; done

.PHONY: test clean memtest all run_freq_count
