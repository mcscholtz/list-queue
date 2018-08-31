#include "suite.h"
#include "ll.h"
#include <string.h>


void ll_s_topstack(CuTest * tc)
{
    const int LOOPS = 1000000;
    struct ll * list = ll_new(SINGLE);
    
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),SINGLE);
        
        list->push_front(list, node);
        CuAssertIntEquals(tc, list->length, i+1);
    }

    for(int i = LOOPS; i > 0; i--){
        struct ln * node = list->pop_front(list);
        CuAssertIntEquals(tc, list->length, i-1);
        ll_delete_node(node);
    }
    
    ll_delete(list);
}


int main(void) { return execute(ll_s_topstack);}