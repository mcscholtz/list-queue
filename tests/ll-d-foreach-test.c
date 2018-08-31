#include "suite.h"
#include "ll.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void add1(void * element)
{
    *(int *)element += 1;
}

void ll_d_foreach(CuTest * tc)
{
    const int LOOPS = 100000;
    struct ll * list = ll_new(DOUBLE);
    //add nodes
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),DOUBLE);
        list->push_back(list, node);
        CuAssertIntEquals(tc, list->length, i+1);
    }

    
    list->foreach(list,add1);

    //validate
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = list->pop_front(list);
        CuAssertIntEquals(tc, *(int *)node->data, i+1);
    }

    ll_delete(list);
}



int main(void) { return execute(ll_d_foreach);}