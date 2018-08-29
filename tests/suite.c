#include "cutest.h"
#include <stdio.h>

int execute(void(*test)(CuTest *tc))
{
    CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test);

	CuString *output = CuStringNew();

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	int fails = suite->failCount;

	CuSuiteDelete(suite);
	CuStringDelete(output);

	return fails;
}