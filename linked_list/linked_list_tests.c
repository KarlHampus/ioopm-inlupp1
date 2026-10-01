#include <CUnit/Basic.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"
#include "../common.h"

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

// General tests
void test_test()
{
    CU_ASSERT_TRUE(true);
}

// Create and destroy
void test_create_destroy()
{
    ioopm_list_t *l = ioopm_list_create();

    CU_ASSERT_PTR_NOT_NULL_FATAL(l);

    ioopm_list_destroy(l);
}

// Is empty
void test_is_empty_on_empty()
{
    ioopm_list_t *l = ioopm_list_create();

    CU_ASSERT_TRUE(ioopm_list_is_empty(l));

    ioopm_list_destroy(l);
}

// Is empty / Append
void test_is_empty_on_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(1));

    CU_ASSERT_FALSE(ioopm_list_is_empty(l));

    ioopm_list_destroy(l);
}

// Get / Append
void test_append_get_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

// Get / Append
void test_append_get_twice()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_append(l, int_elem(20));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(20).i);

    ioopm_list_destroy(l);
}

// Get / Append
void test_get_append_many_times()
{
    ioopm_list_t *l = ioopm_list_create();

    for (elem_t elem = int_elem(0); elem.i < 20; elem.i++)
    {
        ioopm_list_append(l, elem);
    }

    for (elem_t elem = int_elem(0); elem.i < 20; elem.i++)
    {
        CU_ASSERT_EQUAL(ioopm_list_get(l, elem.i).i, elem.i);
    }

    ioopm_list_destroy(l);
}

// Append / Prepend
void test_append_and_prepend()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_prepend(l, int_elem(20));
    ioopm_list_prepend(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(30).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(20).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 2).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 3).i, int_elem(40).i);

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(4).i);

    ioopm_list_destroy(l);
}

// Append / Remove
void test_remove_on_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(10).i);
    CU_ASSERT_TRUE(ioopm_list_is_empty(l));

    ioopm_list_destroy(l);
}

// Append / Remove
void test_append_after_remove()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_remove(l, 0);

    ioopm_list_append(l, int_elem(20));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(20).i);

    ioopm_list_destroy(l);
}

// Remove / Size
void test_remove_on_multiple_values()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    CU_ASSERT_EQUAL(ioopm_list_remove(l, 2).i, int_elem(30).i);
    CU_ASSERT_EQUAL(ioopm_list_remove(l, 2).i, int_elem(40).i);

    // Check that remove lowers size
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(2).i);

    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(20).i);

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(0).i);

    ioopm_list_destroy(l);
}

// Prepend
void test_prepend_once()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_prepend(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

void test_prepend_twice()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_prepend(l, int_elem(10));
    ioopm_list_prepend(l, int_elem(20));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(20).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

void test_prepend_many_times()
{
    ioopm_list_t *l = ioopm_list_create();

    for (elem_t elem = int_elem(0); elem.i < 20; elem.i++)
    {
        ioopm_list_prepend(l, elem);
    }

    // Check first, middle and, last, then size
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(19).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 9).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 19).i, int_elem(0).i);
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(20).i);

    ioopm_list_destroy(l);
}

// Prepend / Remove
void test_prepend_remove()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_prepend(l, int_elem(10));
    ioopm_list_prepend(l, int_elem(20));

    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(20).i);

    ioopm_list_prepend(l, int_elem(30));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(30).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(10).i);

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(2).i);

    ioopm_list_destroy(l);
}

// Size
void test_size_empty()
{
    ioopm_list_t *l = ioopm_list_create();

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(0).i);

    ioopm_list_destroy(l);
}

// Size
void test_size_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(1).i);

    ioopm_list_destroy(l);
}


// Size
void test_size_two_values()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_append(l, int_elem(20));
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(2).i);

    ioopm_list_destroy(l);
}

// Size
void test_size_many_values()
{
    ioopm_list_t *l = ioopm_list_create();

    for (elem_t elem = int_elem(0); elem.i < 20; elem.i++)
    {
        ioopm_list_append(l, elem);
    }

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(20).i);

    ioopm_list_destroy(l);
}

// Head (idk what should happen here, should it be possible?)
// void test_head_empty()
// {
//     ioopm_list_t *l = ioopm_list_create();

//     ioopm_list_head(l);

//     ioopm_list_destroy(l);
// }


// Head
void test_head_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

// Head / Append / Prepend
void test_head_prepend_append()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_prepend(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_prepend(l, int_elem(40));
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(40).i);

    ioopm_list_destroy(l);
}

// Head / Remove
void test_head_after_remove_first()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    ioopm_list_remove(l, 0);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(20).i);

    ioopm_list_remove(l, 0);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(30).i);

    ioopm_list_destroy(l);
}

// Head / Remove
void test_head_after_remove_not_first()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    ioopm_list_remove(l, 3);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_remove(l, 1);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_remove(l, 1);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

// Last
void test_last_singleton()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

// Last / Append / Prepend
void test_last_prepend_append()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_prepend(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(10).i);

    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(30).i);

    ioopm_list_prepend(l, int_elem(40));
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(30).i);

    ioopm_list_destroy(l);
}

// Last / Remove
void test_last_after_remove_last()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    ioopm_list_remove(l, 3);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(30).i);

    ioopm_list_remove(l, 2);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(20).i);

    ioopm_list_remove(l, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

// Last / Remove
void test_last_after_remove_not_last()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_append(l, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(10).i);

    ioopm_list_append(l, int_elem(20));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_append(l, int_elem(40));

    ioopm_list_remove(l, 0);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(40).i);

    ioopm_list_remove(l, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(40).i);

    ioopm_list_remove(l, 1);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(20).i);

    ioopm_list_destroy(l);
}

// Insert
void test_insert_once()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_insert(l, 0, int_elem(10));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

void test_insert_twice_first()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_insert(l, 0, int_elem(10));
    ioopm_list_insert(l, 0, int_elem(20));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(20).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(10).i);

    ioopm_list_destroy(l);
}

void test_insert_twice_last()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_insert(l, 0, int_elem(10));
    ioopm_list_insert(l, 1, int_elem(20));
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(20).i);

    ioopm_list_destroy(l);
}

void test_insert_many_times()
{
    ioopm_list_t *l = ioopm_list_create();

    for (elem_t elem = int_elem(0); elem.i < 20; elem.i++)
    {
        size_t random_index = (elem.i * 32) % (elem.i + 1);
        ioopm_list_insert(l, random_index, elem);
    }

    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(20).i);

    ioopm_list_insert(l, 0, int_elem(1001));
    ioopm_list_insert(l, 13, int_elem(1002));
    ioopm_list_insert(l, 22, int_elem(1003));

    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(1001).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 13).i, int_elem(1002).i);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(1003).i);

    ioopm_list_destroy(l);
}

// Insert / Append / Prepend
void test_insert_append_prepend()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_insert(l, 0, int_elem(10));
    ioopm_list_append(l, int_elem(20));
    ioopm_list_prepend(l, int_elem(1));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(1).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 1).i, int_elem(10).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 2).i, int_elem(20).i);

    ioopm_list_prepend(l, int_elem(4));
    ioopm_list_append(l, int_elem(30));
    ioopm_list_insert(l, 3, int_elem(15));

    CU_ASSERT_EQUAL(ioopm_list_get(l, 3).i, int_elem(15).i);
    CU_ASSERT_EQUAL(ioopm_list_last(l).i, int_elem(30).i);
    CU_ASSERT_EQUAL(ioopm_list_head(l).i, int_elem(4).i);

    ioopm_list_destroy(l);
}

// Insert / Remove
void test_insert_remove()
{
    ioopm_list_t *l = ioopm_list_create();

    ioopm_list_insert(l, 0, int_elem(10));
    ioopm_list_insert(l, 0, int_elem(20));
    ioopm_list_insert(l, 1, int_elem(30));

    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(20).i);
    CU_ASSERT_EQUAL(ioopm_list_remove(l, 1).i, int_elem(10).i);

    ioopm_list_insert(l, 1, int_elem(40));
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(2).i);
    CU_ASSERT_EQUAL(ioopm_list_get(l, 0).i, int_elem(30).i);

    ioopm_list_remove(l, 0);
    CU_ASSERT_EQUAL(ioopm_list_remove(l, 0).i, int_elem(40).i);
    CU_ASSERT_EQUAL(ioopm_list_size(l), int_elem(0).i);

    ioopm_list_destroy(l);
}



int main()
{
	// First we try to set up CUnit, and exit if we fail
	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	// We then create an empty test suite and specify the name and
	// the it and cleanup functions
	CU_pSuite my_test_suite = CU_add_suite("Linked list suite", init_suite, clean_suite);
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
		(CU_add_test(my_test_suite, "Test test                                          ", 
                     test_test) == NULL) ||
        (CU_add_test(my_test_suite, "[Create/Destroy] Create and destroy.               ", 
                     test_create_destroy) == NULL) ||
		(CU_add_test(my_test_suite, "[Is Empty] Empty.                                  ", 
                     test_is_empty_on_empty) == NULL) ||
		(CU_add_test(my_test_suite, "[Is Empty / Append] Singleton.                     ", 
                     test_is_empty_on_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Append / Get] Singleton.                          ", 
                     test_append_get_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Append / Get] Twice.                              ", 
                     test_append_get_twice) == NULL) ||
		(CU_add_test(my_test_suite, "[Append / Get] Many times.                         ", 
                     test_get_append_many_times) == NULL) ||
		(CU_add_test(my_test_suite, "[Prepend] Once.                                    ", 
                     test_prepend_once) == NULL) ||
		(CU_add_test(my_test_suite, "[Prepend] Twice.                                   ", 
                     test_prepend_twice) == NULL) ||
		(CU_add_test(my_test_suite, "[Prepend] Many times.                              ", 
                     test_prepend_many_times) == NULL) ||
		(CU_add_test(my_test_suite, "[Prepend / Append] A few times.                    ", 
                     test_append_and_prepend) == NULL) ||
		(CU_add_test(my_test_suite, "[Remove] Singleton.                                ", 
                     test_remove_on_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Remove] Multple values.                           ", 
                     test_remove_on_multiple_values) == NULL) ||
		(CU_add_test(my_test_suite, "[Remove / Append] Append after remove.             ", 
                     test_append_after_remove) == NULL) ||
		(CU_add_test(my_test_suite, "[Remove / Prepend] Prepend after remove.           ", 
                     test_prepend_remove) == NULL) ||
		(CU_add_test(my_test_suite, "[Size] Empty.                                      ", 
                     test_size_empty) == NULL) ||
		(CU_add_test(my_test_suite, "[Size] Singleton.                                  ", 
                     test_size_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Size] Two values.                                 ", 
                     test_size_two_values) == NULL) ||
		(CU_add_test(my_test_suite, "[Size] A lot of values.                            ", 
                     test_size_many_values) == NULL) ||
		(CU_add_test(my_test_suite, "[Head] Singleton.                                  ", 
                     test_head_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Head] After remove first.                         ", 
                     test_head_after_remove_first) == NULL) ||
		(CU_add_test(my_test_suite, "[Head / Remove] After remove one other than first. ", 
                     test_head_after_remove_not_first) == NULL) ||
		(CU_add_test(my_test_suite, "[Head / Prepend / Appeend] Multiple values.        ", 
                     test_head_prepend_append) == NULL) ||
		(CU_add_test(my_test_suite, "[Last] Singleton.                                  ", 
                     test_last_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[Last] After remove last.                          ", 
                     test_last_after_remove_last) == NULL) ||
		(CU_add_test(my_test_suite, "[Last / Remove] After remove one other than last.  ", 
                     test_last_after_remove_not_last) == NULL) ||
		(CU_add_test(my_test_suite, "[Last / Prepend / Appeend] Multiple values.        ", 
                     test_last_prepend_append) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] Once.                                     ", 
                     test_insert_once) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] Twice first.                              ", 
                     test_insert_twice_first) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] Twice last.                               ", 
                     test_insert_twice_last) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert] Many values.                              ", 
                     test_insert_many_times) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert / Prepend / Append] Multiple values.       ", 
                     test_insert_append_prepend) == NULL) ||
        (CU_add_test(my_test_suite, "[Insert / Remove] A few values.                    ", 
                     test_insert_remove) == NULL) ||
		0)
	{
		// If adding any of the tests fails, we tear down CUnit and exit
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Set the running mode. Use CU_BRM_VERBOSE for maximum output.
	// Use CU_BRM_NORMAL to only print errors and a summary.
	CU_basic_set_mode(CU_BRM_VERBOSE);

	// This is where the tests are actually run!
	CU_basic_run_tests();

	// Tear down CUnit before exing
	CU_cleanup_registry();
	return CU_get_error();
}
