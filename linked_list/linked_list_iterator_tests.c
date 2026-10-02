#include <CUnit/Basic.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"
#include "linked_list_iterator.h"

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

// Create/Destroy
void test_create_destroy()
{
	ioopm_list_t *l = ioopm_list_create();
	ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);

	CU_ASSERT_PTR_NOT_NULL(it);

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(l);
}

// Iterator at end when empty
void test_at_end_empty()
{
	ioopm_list_t *l = ioopm_list_create();
	ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);

	// Empty list, should be at end
	CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(l);
}

// Iterator not at end and at end singleton / iterator advance
void test_at_end_singleton()
{
	ioopm_list_t *l = ioopm_list_create();

	ioopm_list_append(l, int_elem(1));

	ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);

	// Check not at end
	CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));

	// Advance and check at end
	ioopm_list_iterator_advance(it);
	CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(l);
}

void test_advance_at_end_many_times()
{
	ioopm_list_t *l = ioopm_list_create();

	// Add a lot of elements
	for (int i = 0; i < 100; i++)
	{
		ioopm_list_prepend(l, int_elem(i));
	}

	ioopm_list_iterator_t *it = ioopm_list_iterator_create(l);

	// Advance through the whole list and check at every 30th element
	for (int i = 0; i < 100; i++)
	{
		if (i % 30 == 0) CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
		ioopm_list_iterator_advance(it);
	}

	// Should be at end now
	CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(l);
}

// Iterator current / iterator advance

void test_iterator_current()
{
	ioopm_list_t *lst = ioopm_list_create();
	ioopm_list_append(lst, int_elem(1));
	ioopm_list_append(lst, int_elem(2));
	ioopm_list_append(lst, int_elem(3));
	ioopm_list_iterator_t *it = ioopm_list_iterator_create(lst);

	CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 1);
	ioopm_list_iterator_advance(it);
	CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 2);
	ioopm_list_iterator_advance(it);
	CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 3);

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(lst);
}

void test_iterator_insert()
{

	ioopm_list_t *lst = ioopm_list_create();
	ioopm_list_append(lst, int_elem(1));
	ioopm_list_append(lst, int_elem(2));
	ioopm_list_append(lst, int_elem(3));
	ioopm_list_iterator_t *it = ioopm_list_iterator_create(lst);

	ioopm_list_iterator_advance(it); // 2

	ioopm_list_iterator_insert(it, int_elem(150));				 // Insert 150 between 1 and 2
	CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 2); // Make sure we're still at the same index
	CU_ASSERT_EQUAL(ioopm_list_size(lst), 4);			 // Make sure a new element was inserted.
	CU_ASSERT_EQUAL(ioopm_list_get(lst, 1).i, 150);		 // Make sure the 2nd element is 150

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(lst);
}

void test_iterator_remove()
{
	// Create list [1, 2, 3]
	ioopm_list_t *lst = ioopm_list_create();
	ioopm_list_append(lst, int_elem(1));
	ioopm_list_append(lst, int_elem(2));
	ioopm_list_append(lst, int_elem(3));
	ioopm_list_iterator_t *it = ioopm_list_iterator_create(lst);

	ioopm_list_iterator_advance(it); // 2

	// Remove an element in the middle
	ioopm_list_iterator_remove(it); // Remove number 2

	CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 3); // Make sure we're at the next index
	CU_ASSERT_EQUAL(ioopm_list_size(lst), 2);			 // Make sure the size reflects the change

	// Remove an element at the end

	ioopm_list_iterator_remove(it);			   // Delete the last element
	CU_ASSERT(ioopm_list_iterator_at_end(it)); // Make sure we're at the end
	CU_ASSERT_EQUAL(ioopm_list_size(lst), 1);  // Make sure the size reflects the change

	CU_ASSERT_EQUAL(ioopm_list_get(lst, 0).i, 1); // Make sure the remaining element is the number 1

	ioopm_list_iterator_destroy(it);
	ioopm_list_destroy(lst);
}

int main()
{
	// First we try to set up CUnit, and exit if we fail
	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	// We then create an empty test suite and specify the name and
	// the init and cleanup functions
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
		(CU_add_test(my_test_suite, "Test test                      ",
					 test_test) == NULL) ||
		(CU_add_test(my_test_suite, "[Create / Destroy] Once.       ",
					 test_create_destroy) == NULL) ||
		(CU_add_test(my_test_suite, "[At End] Empty.                ",
					 test_at_end_empty) == NULL) ||
		(CU_add_test(my_test_suite, "[At End / Advance] Singleton.  ",
					 test_at_end_singleton) == NULL) ||
		(CU_add_test(my_test_suite, "[At End / Advance] Many times. ",
					 test_advance_at_end_many_times) == NULL) ||
		(CU_add_test(my_test_suite, "[Current] Different values.    ",
					 test_iterator_current) == NULL) ||
		(CU_add_test(my_test_suite, "[Insert] A few times.          ",
					 test_iterator_insert) == NULL) ||
		(CU_add_test(my_test_suite, "[Remove] Some elements.        ",
					 test_iterator_remove) == NULL) ||
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
