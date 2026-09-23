hash_table_iterator_tests: hash_table_iterator_tests.c hash_table_iterator.o
	gcc --coverage -g -Wall -Wextra -pedantic hash_table_iterator_tests.c hash_table.o hash_table_iterator.o -o hash_table_iterator_tests -lcunit

hash_table_iterator.o: hash_table_iterator.c hash_table_iterator.h hash_table.o
	gcc --coverage -c -g -Wall -Wextra -pedantic hash_table_iterator.c -o hash_table_iterator.o

hash_table_tests: hash_table_tests.c hash_table.o
	gcc --coverage -g -Wall -Wextra -pedantic hash_table_tests.c hash_table.o -o hash_table_tests -lcunit

hash_table.o: hash_table.c hash_table.h hash_table_structs.h
	gcc --coverage -c -g -Wall -Wextra -pedantic hash_table.c -o hash_table.o
