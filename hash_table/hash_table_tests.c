#include <CUnit/Basic.h>
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

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
static void insert_and_assert_correct(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
    // Insert value 1 with key 2, should replace old value
    ioopm_hash_table_insert(ht, key, value);

    // Check if lookup with key 2 gives value 1.
    elem_t result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(value.i, result.i);
}

// Test functions
// Create and destroy
void test_create_destroy()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(ht);
}

void test_create_destroy_different_sizes()
{
    // Create the tables
    ioopm_hash_table_t *ht1 = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    ioopm_hash_table_t *ht2 = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    ioopm_hash_table_t *ht3 = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    ioopm_hash_table_t *ht4 = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    ioopm_hash_table_t *ht5 = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Check that they are pointing to something
    CU_ASSERT_PTR_NOT_NULL(ht1);
    CU_ASSERT_PTR_NOT_NULL(ht2);
    CU_ASSERT_PTR_NOT_NULL(ht3);
    CU_ASSERT_PTR_NOT_NULL(ht4);
    CU_ASSERT_PTR_NOT_NULL(ht5);

    // Destroy
    ioopm_hash_table_destroy(ht1);
    ioopm_hash_table_destroy(ht2);
    ioopm_hash_table_destroy(ht3);
    ioopm_hash_table_destroy(ht4);
    ioopm_hash_table_destroy(ht5);
}

// Lookup
void test_lookup_on_empty_table()
{
    // create new hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");

    // Check that lookup on empty ht returns false
    elem_t result = int_elem(0);
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(result.i, 0);

    ioopm_hash_table_destroy(ht);
}

void test_lookup_on_singleton()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");
    elem_t value = int_elem(123);

    // insert key-value pair and check that the mapping exists
    ioopm_hash_table_insert(ht, key, value);

    // Check that lookup is successful and has correct value
    elem_t result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
    CU_ASSERT_EQUAL(result.i, value.i);

    // destroy hash table
    ioopm_hash_table_destroy(ht);
}

void test_lookup_on_table_with_two_elements()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t value1 = int_elem(123);
    elem_t value2 = int_elem(1234);

    // insert key-value pair and check that the mapping exists
    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);

    // Check that lookup is successful and has correct values
    elem_t result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key1, &result));
    CU_ASSERT_EQUAL(result.i, value1.i);

    result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key2, &result));
    CU_ASSERT_EQUAL(result.i, value2.i);

    // destroy hash table
    ioopm_hash_table_destroy(ht);
}

void test_lookup_of_wrong_key_on_table_with_elements()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t key3 = string_elem("abcde");
    elem_t value1 = int_elem(123);
    elem_t value2 = int_elem(1234);

    // insert key-value pair and check that the mapping exists
    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);

    // Check that lookup is successful and has correct values
    elem_t result = int_elem(0);
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key3, &result));
    CU_ASSERT_EQUAL(result.i, 0);

    // destroy hash table
    ioopm_hash_table_destroy(ht);
}

void test_lookup_on_elements_in_same_bucket()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // All of these keys hash to 4 with No_Buckets = 17
    elem_t key1 = string_elem("Aa");
    elem_t key2 = string_elem("BB");
    elem_t key3 = string_elem("abcd");
    elem_t value1 = int_elem(1);
    elem_t value2 = int_elem(2);
    elem_t value3 = int_elem(3);

    // Inserts the keys with the same hash to the same bucket
    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    // Check that lookup correctly looks up the correct value
    elem_t result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key1, &result));
    CU_ASSERT_EQUAL(result.i, value1.i);

    result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key2, &result));
    CU_ASSERT_EQUAL(result.i, value2.i);

    result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key3, &result));
    CU_ASSERT_EQUAL(result.i, value3.i);

    // Destroy
    ioopm_hash_table_destroy(ht);
}

// Insert
void test_insert_once()
{
    // create new hash table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");
    elem_t value = int_elem(123);

    // insert key-value pair and check that the mapping exists
    elem_t result = int_elem(0);
    ioopm_hash_table_insert(ht, key, value);

    // Validate that the inserted value can be found and is correct
    ioopm_hash_table_lookup(ht, key, &result);
    CU_ASSERT_EQUAL(result.i, value.i);

    // destroy hash table
    ioopm_hash_table_destroy(ht);
}

void test_insert_already_exisiting_key()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Initial key value pairs
    elem_t key = string_elem("abc");
    elem_t value = int_elem(123);
    elem_t value2 = int_elem(321);

    // Testing insert and change value of key 1
    ioopm_hash_table_insert(ht, key, value);
    insert_and_assert_correct(ht, key, value2);

    // Destroy the hash_table
    ioopm_hash_table_destroy(ht);
}

void test_insert_already_existing_key_into_ht_with_values()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t key3 = string_elem(""); // Empty string, should be possible :)
    elem_t value = int_elem(123);
    elem_t value2 = int_elem(321);
    elem_t value3 = int_elem(1);

    ioopm_hash_table_insert(ht, key, value);

    // Testing insert and change value of key 2
    ioopm_hash_table_insert(ht, key2, value2);
    insert_and_assert_correct(ht, key2, value);

    // Testing insert and change value of key 3
    ioopm_hash_table_insert(ht, key3, value3);
    insert_and_assert_correct(ht, key3, value);

    // Testing insert and change value of key 1 after key 2 and 3 are in ht
    insert_and_assert_correct(ht, key, value3);

    ioopm_hash_table_destroy(ht);
}

void test_insert_two_elements_with_same_key_adress_different_values()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("a");
    elem_t initial_key = string_elem(strdup(key.s));
    elem_t value = int_elem(123);
    elem_t value2 = int_elem(321);

    // Insert
    ioopm_hash_table_insert(ht, key, value);
    key.s = "b";
    ioopm_hash_table_insert(ht, key, value2);

    // Check if correct
    elem_t result = int_elem(0);
    ioopm_hash_table_lookup(ht, initial_key, &result);
    CU_ASSERT_EQUAL(result.i, value.i);

    result = int_elem(0);
    ioopm_hash_table_lookup(ht, key, &result);
    CU_ASSERT_EQUAL(result.i, value2.i);

    // Destroy
    free(initial_key.s);
    ioopm_hash_table_destroy(ht);
}

// Remove
void test_remove_entry_empty_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Test removing a non existing key
    elem_t result = int_elem(0);
    CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, string_elem("abc"), &result));
    CU_ASSERT_EQUAL(result.i, 0);

    ioopm_hash_table_destroy(ht);
}

void test_remove_one_entry()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Initial key value pairs
    elem_t key = string_elem("abc");
    elem_t value = int_elem(123);

    // Insert test values
    ioopm_hash_table_insert(ht, key, value);

    // Test removing the last element in a bucket
    elem_t result = int_elem(0);
    CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, key, &result));
    CU_ASSERT_EQUAL(result.i, value.i);

    // Test to make sure element was removed properly
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));

    ioopm_hash_table_destroy(ht);
}

void test_removing_one_entry_with_multiple_values_in_ht()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Initial key value pairs
    elem_t key = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t key3 = string_elem(""); // Empty string, should be possible :)
    elem_t value = int_elem(123);
    elem_t value2 = int_elem(321);
    elem_t value3 = int_elem(1);

    // Insert test data
    ioopm_hash_table_insert(ht, key, value);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    // Test removing existing key in the middle
    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, key2, &result);
    CU_ASSERT_EQUAL(result.i, value2.i);

    // Check that value is removed
    result = int_elem(0);
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key2, &result));

    // Check if other values are left
    result = int_elem(0);
    ioopm_hash_table_lookup(ht, key, &result);
    CU_ASSERT_EQUAL(result.i, value.i);

    result = int_elem(0);
    ioopm_hash_table_lookup(ht, key3, &result);
    CU_ASSERT_EQUAL(result.i, value3.i);

    ioopm_hash_table_destroy(ht);
}

void test_removing_from_same_bucket()
{
    // Creates a new hash_table
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // All of these keys hash to 4 with No_Buckets = 17
    elem_t key1 = string_elem("Aa");
    elem_t key2 = string_elem("BB");
    elem_t key3 = string_elem("abcd");
    elem_t value1 = int_elem(1);
    elem_t value2 = int_elem(2);
    elem_t value3 = int_elem(3);

    // Inserts the keys with the same hash to the same bucket
    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    // Check if correct value is removed from the bucket.
    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, key2, &result);
    CU_ASSERT_EQUAL(result.i, value2.i);

    // Check if the other values in the same bucket are left.
    result = int_elem(0);
    ioopm_hash_table_lookup(ht, key1, &result);
    CU_ASSERT_EQUAL(result.i, value1.i);

    result = int_elem(0);
    ioopm_hash_table_lookup(ht, key3, &result);
    CU_ASSERT_EQUAL(result.i, value3.i);

    ioopm_hash_table_destroy(ht);
}

// Has key
void test_ht_has_nonexisting_key()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, string_elem("abc")));

    ioopm_hash_table_destroy(ht);
}

void test_ht_has_existing_key()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");
    elem_t value = int_elem(92);
    ioopm_hash_table_insert(ht, key, value);

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));

    ioopm_hash_table_destroy(ht);
}

void test_ht_has_multiple_keys()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t key3 = string_elem("abcde");
    elem_t value1 = int_elem(101);
    elem_t value2 = int_elem(202);
    elem_t value3 = int_elem(303);

    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key1));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key2));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));

    ioopm_hash_table_destroy(ht);
}

void test_ht_has_removed_key()
{

    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key = string_elem("abc");
    elem_t value = int_elem(92);
    ioopm_hash_table_insert(ht, key, value);

    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, key, &result);

    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

    ioopm_hash_table_destroy(ht);
}

void test_ht_has_one_removed_two_remaining_keys()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("abc");
    elem_t key2 = string_elem("abcd");
    elem_t key3 = string_elem("abcde");
    elem_t value1 = int_elem(101);
    elem_t value2 = int_elem(202);
    elem_t value3 = int_elem(303);

    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);

    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, key2, &result);

    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key1));
    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));

    ioopm_hash_table_destroy(ht);
}

// Size
void test_size_of_empty_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_singleton_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    ioopm_hash_table_insert(ht, string_elem("abc"), int_elem(1));

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_two_element_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    ioopm_hash_table_insert(ht, string_elem("abc"), int_elem(1));
    ioopm_hash_table_insert(ht, string_elem("abcd"), int_elem(2));

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_two_element_same_bucket_ht()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    // Same bucket for 17 buckets !!!!
    ioopm_hash_table_insert(ht, string_elem("Aa"), int_elem(1));
    ioopm_hash_table_insert(ht, string_elem("BB"), int_elem(2));

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_ht_after_one_remove()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    ioopm_hash_table_insert(ht, string_elem("abc"), int_elem(1));
    ioopm_hash_table_insert(ht, string_elem("abcd"), int_elem(2));
    ioopm_hash_table_insert(ht, string_elem("abcde"), int_elem(3));

    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, string_elem("abcd"), &result);

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 2);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_ht_after_remove_of_last_element()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    ioopm_hash_table_insert(ht, string_elem("abc"), int_elem(1));

    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, string_elem("abc"), &result);

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

    ioopm_hash_table_destroy(ht);
}

void test_size_of_ht_after_many_inserts()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    ioopm_set_on_destroy_entry(ht, &ioopm_string_key_destroy);

    int total_inserts = 0;
    char key[4];
    key[3] = '\0';

    for (char ch1 = 'a'; ch1 <= 'z'; ch1++)
    {
        key[0] = ch1;
        for (char ch2 = 'a'; ch2 <= 'z'; ch2++)
        {
            key[1] = ch2;
            for (char ch3 = 'a'; ch3 <= 'z'; ch3++)
            {
                key[2] = ch3;

                ioopm_hash_table_insert(ht, string_elem(strdup(key)), int_elem(total_inserts));
                total_inserts++;
            }
        }
    }

    CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), total_inserts);

    ioopm_hash_table_destroy(ht);
}

// Is empty
void test_empty_hash_table_is_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

    ioopm_hash_table_destroy(ht);
}

void test_singleton_hash_table_is_not_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("key1");
    elem_t value1 = int_elem(123);

    ioopm_hash_table_insert(ht, key1, value1);
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

    ioopm_hash_table_destroy(ht);
}

void test_larger_hash_table_is_not_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("key1");
    elem_t key2 = string_elem("key2");
    elem_t key3 = string_elem("key3");
    elem_t value1 = int_elem(123);
    elem_t value2 = int_elem(456);
    elem_t value3 = int_elem(789);

    ioopm_hash_table_insert(ht, key1, value1);
    ioopm_hash_table_insert(ht, key2, value2);
    ioopm_hash_table_insert(ht, key3, value3);
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

    ioopm_hash_table_destroy(ht);
}

void test_hash_table_insert_then_remove_is_empty()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(&ioopm_string_hash, &ioopm_string_equal);

    elem_t key1 = string_elem("key1");
    elem_t value1 = int_elem(123);

    ioopm_hash_table_insert(ht, key1, value1);
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

    elem_t result = int_elem(0);
    ioopm_hash_table_remove(ht, key1, &result);
    CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

    ioopm_hash_table_destroy(ht);
}

// Main
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
        // Create and destroy test
        (CU_add_test(my_test_suite, "[Create and destroy] one ht.",
                     test_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "[Create and destroy] multiple ht of different bucket sizes.",
                     test_create_destroy_different_sizes) == NULL) ||

        // Lookup tests
        (CU_add_test(my_test_suite, "[Lookup] empty ht.",
                     test_lookup_on_empty_table) == NULL) ||
        (CU_add_test(my_test_suite, "[Lookup] singleton.",
                     test_lookup_on_singleton) == NULL) ||
        (CU_add_test(my_test_suite, "[Lookup] table with two elements.",
                     test_lookup_on_table_with_two_elements) == NULL) ||
        (CU_add_test(my_test_suite, "[Lookup] wrong key on table with elements.",
                     test_lookup_of_wrong_key_on_table_with_elements) == NULL) ||
        (CU_add_test(my_test_suite, "[Lookup] elements in same bucket.",
                     test_lookup_on_elements_in_same_bucket) == NULL) ||

        // Insert tests
        (CU_add_test(my_test_suite, "[Insert] once.",
                     test_insert_once) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] already exisiting key.",
                     test_insert_already_exisiting_key) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] same keys into ht with other exisiting elements.",
                     test_insert_already_existing_key_into_ht_with_values) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] same pointer but different values.",
                     test_insert_two_elements_with_same_key_adress_different_values) == NULL) ||

        // Remove tests
        (CU_add_test(my_test_suite, "[Remove] entries from empty ht.",
                     test_remove_entry_empty_ht) == NULL) ||
        (CU_add_test(my_test_suite, "[Remove] one entry.",
                     test_remove_one_entry) == NULL) ||
        (CU_add_test(my_test_suite, "[Remove] from same bucket.",
                     test_removing_from_same_bucket) == NULL) ||
        (CU_add_test(my_test_suite, "[Remove] multiple values from ht with multiple values.",
                     test_removing_one_entry_with_multiple_values_in_ht) == NULL) ||

        // Has key tests
        (CU_add_test(my_test_suite, "[Has Key] doesnt have nonexisting key.",
                     test_ht_has_nonexisting_key) == NULL) ||
        (CU_add_test(my_test_suite, "[Has Key] has existing key.",
                     test_ht_has_existing_key) == NULL) ||
        (CU_add_test(my_test_suite, "[Has Key] has multiple keys.",
                     test_ht_has_multiple_keys) == NULL) ||
        (CU_add_test(my_test_suite, "[Has Key] doesnt have removed key.",
                     test_ht_has_removed_key) == NULL) ||
        (CU_add_test(my_test_suite, "[Has Key] doesnt have removed key but others remain.",
                     test_ht_has_one_removed_two_remaining_keys) == NULL) ||

        // Size tests
        (CU_add_test(my_test_suite, "[Size] empty ht.",
                     test_size_of_empty_ht) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] singleton ht.",
                     test_size_of_singleton_ht) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] two element ht.",
                     test_size_of_two_element_ht) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] two elements in same bucket ht.",
                     test_size_of_two_element_same_bucket_ht) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] after one remove.",
                     test_size_of_ht_after_one_remove) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] after removing last element.",
                     test_size_of_ht_after_remove_of_last_element) == NULL) ||
        (CU_add_test(my_test_suite, "[Size] after many inserts.",
                     test_size_of_ht_after_many_inserts) == NULL) ||

        // Is empty tests
        (CU_add_test(my_test_suite, "[Is Empty] empty.",
                     test_empty_hash_table_is_empty) == NULL) ||
        (CU_add_test(my_test_suite, "[Is Empty] singleton not empty.",
                     test_singleton_hash_table_is_not_empty) == NULL) ||
        (CU_add_test(my_test_suite, "[Is Empty] larger ht not empty.",
                     test_larger_hash_table_is_not_empty) == NULL) ||
        (CU_add_test(my_test_suite, "[Is Empty] is empty after insert then remove.",
                     test_hash_table_insert_then_remove_is_empty) == NULL) ||
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