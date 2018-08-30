#include "suite.h"
#include "ll.h"
#include <string.h>


void ll_s_createlist(CuTest * tc)
{    
    struct ll * list = ll_new(SINGLE);
    CuAssertIntEquals(tc, list->length, 0);
    CuAssertIntEquals(tc, list->type, SINGLE);
    ll_delete(list);    
}

int main(void) { return execute(ll_s_createlist);}