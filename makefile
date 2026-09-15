hash_table_tests: hash_table_tests.c hash_table.o
	gcc -g -Wall -Wextra -pedantic hash_table_tests.c hash_table.o -o hash_table_tests -lcunit

hash_table.o: hash_table.c hash_table.h
	gcc -c -g -Wall -Wextra -pedantic hash_table.c