#include "suite.h"
#include "ll.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void ll_s_popat(CuTest * tc)
{
    const int LOOPS = 100000;
    struct ll * list = ll_new(SINGLE);
    //add nodes
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),SINGLE);
        list->push_back(list, node);
        CuAssertIntEquals(tc, list->length, i+1);
    }

    for(int i = 0; i < LOOPS-1; i++){
        struct ln * node = list->pop_at(list,1);
        CuAssertIntEquals(tc, list->length, LOOPS-(i+1));
        CuAssertIntEquals(tc, i+1, *(int *)node->data);
    }
    ll_delete(list);
}


int main(void) { return execute(ll_s_popat);}