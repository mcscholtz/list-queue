#include "cutest.h"

int execute(CuSuite* test)
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