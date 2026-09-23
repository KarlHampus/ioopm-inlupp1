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
void test_iterating_ht_multiple_values()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(17);
    ioopm_hash_table_t *ht_control = ioopm_hash_table_create(17);

    char *key1 = "aa";
    char *key2 = "ab";
    char *key3 = "ac";
    char *key4 = "ax";
    char *key5 = "ah";
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    int val5 = 5;

    ioopm_hash_table_insert(ht, key1, val1);
    ioopm_hash_table_insert(ht, key2, val2);
    ioopm_hash_table_insert(ht, key3, val3);
    ioopm_hash_table_insert(ht, key4, val4);
    ioopm_hash_table_insert(ht, key5, val5);

    // Hash table to check that values have been visited
    ioopm_hash_table_insert(ht_control, key1, val1);
    ioopm_hash_table_insert(ht_control, key2, val2);
    ioopm_hash_table_insert(ht_control, key3, val3);
    ioopm_hash_table_insert(ht_control, key4, val4);
    ioopm_hash_table_insert(ht_control, key5, val5);

    // Create iterator
    ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

    // Adding to avoid infinite loops in case advance does not work
    int safety_line = 10;
    while (!ioopm_hash_table_iterator_at_end(it) && safety_line > 0)
    {
        char *cur_key = ioopm_hash_table_iterator_current_key(it);

        // Check that the control table has the same key
        CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht_control, cur_key));

        // Remove the key from the control table to ensure there are
        // no dups in the future checks
        int result = 0;
        ioopm_hash_table_remove(ht_control, cur_key, &result);

        // Advance iterator and decrease safety line
        ioopm_hash_table_iterator_advance(it);
        safety_line--;
    }

    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht_control));

    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy(ht);
    ioopm_hash_table_destroy(ht_control);
}

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
    (CU_add_test(my_test_suite, "[Iteration] Empty table.", test_iterating_empty_table) == NULL) ||
    (CU_add_test(my_test_suite, "[Iteration] Singleton.", test_iterating_singleton_ht ) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
