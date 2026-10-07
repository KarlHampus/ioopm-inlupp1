#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table/hash_table.h"
#include "hash_table/hash_table_iterator.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

/// @brief Process a single word, updating its frequency
/// @param word the word to process
/// @param ht a hash table containing the frequencies of the words found so far.
void process_word(char *word, ioopm_hash_table_t *ht)
{
	elem_t freq = int_elem(0);
	elem_t key = string_elem(word);
	ioopm_hash_table_lookup(ht, key, &freq);

	if (freq.i == 0) key = string_elem(strdup(word));

	ioopm_hash_table_insert(ht, key, int_elem(freq.i + 1));
}

/// @brief Process a single file, updating the frequencies of its words
/// @param filename the name of the file to process
/// @param ht a hash table containing the frequencies of the words found so far
void process_file(char *filename, ioopm_hash_table_t *ht)
{
	printf("Filename: %s\n", filename);
	FILE *f = fopen(filename, "r");

	while (!feof(f))
	{
		char *buf = NULL;
		size_t len = 0;

		if (getline(&buf, &len, f) == -1)
		{
			free(buf);
			break;
		}

		for (char *word = strtok(buf, Delimiters);
			 word && *word;
			 word = strtok(NULL, Delimiters))
		{
			process_word(word, ht);
		}

		free(buf);
	};
	fclose(f);
}

/// @brief A word together with its frequency
struct freq_word
{
	char *word;
	int freq;
};

/// @brief Compare the frequency of two freq_words through pointers to them
/// @param p1 the first freq_word
/// @param p2 the second freq_word
/// @return a number @n@:
///     @n@ > 0  if @p1@'s frequency is higher than @p2@'s
///     @n@ < 0  if @p1@'s frequency is lower than @p2@'s
///     @n@ == 0 if @p1@'s frequency is equal to @p2@'s
static int cmp_freq_words(const void *p1, const void *p2)
{
	const struct freq_word *w1 = p1;
	const struct freq_word *w2 = p2;

	return w1->freq - w2->freq;
}

/// @brief Like @cmp_freq_words@ but with the comparison result reversed
static int cmp_freq_words_reverse(const void *p1, const void *p2)
{
	return -cmp_freq_words(p1, p2);
}

void add_elements_from_ht_to_array(ioopm_hash_table_t *ht, struct freq_word words[])
{
	ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

	while (!ioopm_hash_table_iterator_at_end(it))
	{
		struct freq_word f_word = {
			.freq = ioopm_hash_table_iterator_current_value(it).i,
			.word = ioopm_hash_table_iterator_current_key(it).s
		};

		*words = f_word;
		words++;

		ioopm_hash_table_iterator_advance(it);
	}

	ioopm_hash_table_iterator_destroy(it);
}

/// @brief Sort an array of @freq_word@s in descending frequency order
/// @param words the array to be sorted
/// @param no_words the number of elements in the array
void sort_freq_words(struct freq_word words[], size_t no_words)
{
	qsort(words, no_words, sizeof(struct freq_word), cmp_freq_words_reverse);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s file1 ... filen", argv[0]);
		return 1;
	}

	ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
	ioopm_set_on_destroy_entry(ht, &ioopm_string_key_destroy);

	for (int i = 1; i < argc; ++i)
	{
		process_file(argv[i], ht);
	}

	int size = ioopm_hash_table_size(ht);
	struct freq_word freq_words[size];

	add_elements_from_ht_to_array(ht, freq_words);

	sort_freq_words(freq_words, size);

	for (int i = 0; i < size; ++i)
	{
		printf("%s: %d\n", freq_words[i].word, freq_words[i].freq);
	}

	ioopm_hash_table_destroy(ht);
}
