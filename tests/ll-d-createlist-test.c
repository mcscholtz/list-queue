#include "suite.h"
#include "ll.h"
#include <string.h>


void ll_d_createlist(CuTest * tc)
{
    struct ll * list = ll_new(DOUBLE);
    CuAssertIntEquals(tc, list->length, 0);
    CuAssertIntEquals(tc, list->type, DOUBLE);
    ll_delete(list);
}

int main(void) { return execute(ll_d_createlist);}