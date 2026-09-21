#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void)
{
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}

int clean_suite(void)
{
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}

// Function for testing repeated insert and lookups easier
static void test_insert(ioopm_hash_table_t *ht, char *key, int value)
{
    // Insert value 1 with key 2, should replace old value
    ioopm_hash_table_insert(ht, key, value);

    // Check if lookup with key 2 gives value 1.
    int result = 0;
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(value, result);
}

// Test functions
void test_create_destroy()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void test_lookup_on_empty_table()
{
    // create new hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    char *key = "abc";

    // Check that lookup on empty ht returns false
    int result = 0;
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(result, 0);

    ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
    // create new hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    char *key = "abc";
    int value = 123;

    // insert key-value pair and check that the mapping exists
    int result = 0;
    ioopm_hash_table_insert(ht, key, value);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(result, value);

    // destroy hash table
    ioopm_hash_table_destroy(ht);
}

void test_remove_entry_empty_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // Test removing a non existing key
    int result = 0;
    CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, "abc", &result));
    CU_ASSERT_EQUAL(result, 0);

    ioopm_hash_table_destroy(ht);
}

void test_remove_one_entry()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // Initial key value pairs
    char *key = "abc";
    int value = 123;

    // Insert test values
    ioopm_hash_table_insert(ht, key, value);

    // Test removing the last element in a bucket
    int result = 0;
    CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &result));
    CU_ASSERT_EQUAL(result, value);

    // Test to make sure element was removed properly
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));

    ioopm_hash_table_destroy(ht);
}

void test_removing_one_entry_with_multiple_values_in_ht()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // Initial key value pairs
    char *key = "abc";
    char *key2 = "abcd";
    char *key3 = ""; // Empty string, should be possible :)
    int value = 123;
    int value2 = 321;
    int value3 = 1;

    // Insert test data
    ioopm_hash_table_insert(ht, key, value);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    // Test removing existing key in the middle
    int result = 0;
    ioopm_hash_table_remove(ht, key2, &result);
    CU_ASSERT_EQUAL(result, value2);

    // Check that value is removed
    result = 0;
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key2, &result));

    // Check if other values are left
    result = 0;
    ioopm_hash_table_lookup(ht, key, &result);
    CU_ASSERT_EQUAL(result, value);

    result = 0;
    ioopm_hash_table_lookup(ht, key3, &result);
    CU_ASSERT_EQUAL(result, value3);

    ioopm_hash_table_destroy(ht);
}

void test_removing_from_same_bucket()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // All of these keys hash to 4 with No_Buckets = 17
    char *key1 = "Aa";
    char *key2 = "BB";
    char *key3 = "abcd";
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;

    // Inserts the keys with the same hash to the same bucket
    ioopm_hash_table_insert(ht, key1, val1);
    ioopm_hash_table_insert(ht, key2, val2);
    ioopm_hash_table_insert(ht, key3, val3);

    // Check if correct value is removed from the bucket.
    int result = 0;
    ioopm_hash_table_remove(ht, key2, &result);
    CU_ASSERT_EQUAL(result, val2);

    // Check if the other values in the same bucket are left.
    result = 0;
    ioopm_hash_table_lookup(ht, key1, &result);
    CU_ASSERT_EQUAL(result, val1);

    result = 0;
    ioopm_hash_table_lookup(ht, key3, &result);
    CU_ASSERT_EQUAL(result, val3);

    ioopm_hash_table_destroy(ht);
}

void test_insert_already_exisiting_key()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    // Initial key value pairs
    char *key = "abc";
    int value = 123;
    int value2 = 321;

    // Testing insert and change value of key 1
    ioopm_hash_table_insert(ht, key, value);
    test_insert(ht, key, value2);

    // Destroy the hash_table
    ioopm_hash_table_destroy(ht);
}

void test_insert_already_existing_key_into_ht_with_values()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create();

    char *key = "abc";
    char *key2 = "abcd";
    char *key3 = ""; // Empty string, should be possible :)
    int value = 123;
    int value2 = 321;
    int value3 = 1;

    ioopm_hash_table_insert(ht, key, value);

    // Testing insert and change value of key 2
    ioopm_hash_table_insert(ht, key2, value2);
    test_insert(ht, key2, value);

    // Testing insert and change value of key 3
    ioopm_hash_table_insert(ht, key3, value3);
    test_insert(ht, key3, value);

    // Testing insert and change value of key 1 after key 2 and 3 are in ht
    test_insert(ht, key, value3);

    ioopm_hash_table_destroy(ht);
}

void test_hash_table_has_nonexisting_key()
{
}

void test_hash_table_has_existing_key()
{
}

void test_hash_table_has_multiple_keys()
{
}

void test_hash_table_has_removed_key()
{
}

void test_hash_table_has_one_removed_two_remaining_keys()
{
}

void test_hash_table_is_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
}

int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("Hash table test suite", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
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
        (CU_add_test(my_test_suite, "Test creating and destroying a hash table.", test_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "Test lookup on empty ht.", test_lookup_on_empty_table) == NULL) ||
        (CU_add_test(my_test_suite, "Test insert and lookup functionality.", test_insert_once) == NULL) ||
        (CU_add_test(my_test_suite, "Test insert on already exisiting key.", test_insert_already_exisiting_key) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing entries from empty ht.", test_remove_entry_empty_ht) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing one entry.", test_remove_one_entry) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing from same bucket.", test_removing_from_same_bucket) == NULL) ||
        (CU_add_test(my_test_suite, "Test removing multiple values from ht with multiple values.",
                     test_removing_one_entry_with_multiple_values_in_ht) == NULL) ||
        (CU_add_test(my_test_suite, "Test inserting same keys into ht with other exisiting elements.",
                     test_insert_already_existing_key_into_ht_with_values) == NULL) ||
        0)
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