#include <CUnit/Basic.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// Test functions
void test_nothing()
{
    CU_ASSERT_TRUE(true);
}

// General tests

// Iterating over an empty hash table
void test_iterating_empty_table()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(2);
    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

    CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy(ht);
}

// Iterating over a hash table with one entry
void test_iterating_singleton_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(2);

    char *key = "abc";
    int val = 123;

    ioopm_hash_table_insert(ht, key, val);

    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

    CU_ASSERT_FALSE(ioopm_hash_table_iterator_at_end(it));
    CU_ASSERT_TRUE(strcmp(ioopm_hash_table_iterator_current_key(it), key) == 0);
    CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it), val);

    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy(ht);
}

// Iterating over a hash table with several entries
// Making sure that every inserted key-value pair is visited exactly once
// Iterating over a hash table with several entries in the same bucket

int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Hash table iterator tests", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "[Nothing] True is true..", test_nothing) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_NORMAL);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
