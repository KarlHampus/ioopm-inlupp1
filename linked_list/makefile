CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=linked_list_iterator_tests

all: linked_list_tests linked_list_iterator_tests
#	./$(TESTFILE)

%.o: %.c %.h common.o
	$(CC) $(FLAGS) $< -c -o $@

linked_list_tests: linked_list_tests.c linked_list.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

linked_list_iterator_tests: linked_list_iterator_tests.c linked_list_iterator.o linked_list.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

linked_list_iterator.o: linked_list_iterator.c linked_list.o
	$(CC) $(FLAGS) $< -c -o $@

common.o:
	make -C ../ common.o

clean:
	rm -f *.o
	rm -f linked_list_tests linked_list_iterator_tests
	rm -f *.gcda *.gcno *.gcov

test: linked_list_iterator_tests
	./$(TESTFILE)

memtest: $(TESTFILE)
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
