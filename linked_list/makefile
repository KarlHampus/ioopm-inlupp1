CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
DEPENDENCIES=linked_list.o linked_list_iterator.o ../common.o

all: linked_list_tests linked_list_iterator_tests
#	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@

%_tests: %_tests.c $(DEPENDENCIES)
	$(CC) $(FLAGS) $^ -o $@ -lcunit

linked_list.o: ../common.h

linked_list_iterator.o: linked_list.h ../common.h

clean:
	rm -f *.o
	rm -f linked_list_tests linked_list_iterator_tests
	rm -f *.gcda *.gcno *.gcov

TEST_SOURCES := $(wildcard *_tests.c)
TESTS := $(TEST_SOURCES:.c=)
test: $(TESTS)
	@for test in $(TESTS); do ./$$test; done

memtest: $(TESTS)
	@for test in $(TESTS); do valgrind --leak-check=full ./$$test; done

coverage:
	@make test -s > /dev/null
	gcov $(COVFLAGS) linked_list.c
	gcov $(COVFLAGS) linked_list_iterator.c

.PHONY: test clean memtest all coverage
