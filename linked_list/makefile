CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=linked_list_iterator_tests
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

test: $(TESTFILE)
	./$(TESTFILE)

memtest: $(TESTFILE)
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
