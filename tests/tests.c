#include "cutest.h"
#include "ll_suite.h"
#include <stdio.h>

CuSuite* ArgUtilGetSuite();
CuSuite* FileUtilGetSuite();

//All tests are executed from this function
void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, LinkedListSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}



int main(void) {
	RunAllTests();
}