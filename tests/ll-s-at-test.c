#include "suite.h"
#include "ll.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void ll_d_at(CuTest * tc)
{
    const int LOOPS = 10000;
    struct ll * list = ll_new(SINGLE);
    //add nodes
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),SINGLE);
        list->push_back(list, node);
        CuAssertIntEquals(tc, list->length, i+1);
    }

    //validate nodes with at function
    for(int i = 0; i < LOOPS; i++){
        int *j = (int *)list->at(list,i);
        CuAssertIntEquals(tc, i, *j);
    }

    ll_delete(list);
}


int main(void) { return execute(ll_d_at);}