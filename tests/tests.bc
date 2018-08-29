#include "cutest.h"
#include "sll_suite.h"
#include "dll_suite.h"
#include <stdio.h>

CuSuite* ArgUtilGetSuite();
CuSuite* FileUtilGetSuite();

//All tests are executed from this function
int RunAllTests(void) {
	int fail_count = 0;

	CuString *sll_output = CuStringNew();
	CuSuite* sll_suite = CuSuiteNew();

	CuSuiteAddSuite(sll_suite, SingleLinkedListSuite());

	printf("Starting Singly Linked List Test\n");
	CuSuiteRun(sll_suite);
	CuSuiteSummary(sll_suite, sll_output);
	CuSuiteDetails(sll_suite, sll_output);
	printf("%s\n", sll_output->buffer);
	fail_count += sll_suite->failCount;
	
	CuString *dll_output = CuStringNew();
	CuSuite* dll_suite = CuSuiteNew();

	CuSuiteAddSuite(dll_suite, DoubleLinkedListSuite());

	printf("Starting Doubly Linked List Test\n");
	CuSuiteRun(dll_suite);
	CuSuiteSummary(dll_suite, dll_output);
	CuSuiteDetails(dll_suite, dll_output);
	printf("%s\n", dll_output->buffer);
	fail_count += dll_suite->failCount;

	CuSuiteDelete(sll_suite);
	CuStringDelete(sll_output);
	CuSuiteDelete(dll_suite);
	CuStringDelete(dll_output);

	return fail_count;
}



int main(void) {
	return RunAllTests();
}