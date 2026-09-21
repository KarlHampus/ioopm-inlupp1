hash_table_tests: hash_table_tests.c hash_table.o
	gcc --coverage -g -Wall -Wextra -pedantic hash_table_tests.c hash_table.o -o hash_table_tests -lcunit

hash_table.o: hash_table.c hash_table.h
	gcc --coverage -c -g -Wall -Wextra -pedantic hash_table.c -o hash_table.o