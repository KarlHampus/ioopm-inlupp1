CC=gcc
FLAGS=--coverage -g -Wall -Wextra -pedantic
TESTFILE=linked_list_tests

all: linked_list_tests
#	./$(TESTFILE)

%.o: %.c %.h
	$(CC) $(FLAGS) $< -c -o $@

linked_list_tests: linked_list_tests.c linked_list.o
	$(CC) $(FLAGS) $^ -o $@ -lcunit

clean:
	rm -f *.o
	rm -f linked_list_tests
	rm -f *.gcda *.gcno *.gcov

test: linked_list_tests
	./$(TESTFILE)

memtest: $(TESTFILE)
	valgrind --leak-check=full ./$(TESTFILE)

.PHONY: test clean memtest all
