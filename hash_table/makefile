CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
DEPENDENCIES=hash_table_iterator.o hash_table.o ../common.o
COVFLAGS=

all: hash_table_iterator_tests hash_table_tests
#	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@

%_tests: %_tests.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -lcunit

hash_table.o: ../common.h

hash_table_iterator.o: hash_table.h ../common.h

clean:
	rm -f *.o
	rm -f hash_table_tests hash_table_iterator_tests
	rm -f *.gcda *.gcno *.gcov

TEST_SOURCES := $(wildcard *_tests.c)
TESTS := $(TEST_SOURCES:.c=)
test: $(TESTS)
	@for test in $(TESTS); do ./$$test; done

memtest: $(TESTS)
	@for test in $(TESTS); do valgrind --leak-check=full ./$$test; done

coverage:
	@make test -s > /dev/null
	gcov hash_table.c $(COVFLAGS)
	gcov hash_table_iterator.c $(COVFLAGS)

.PHONY: test clean memtest all coverage
