#include "suite.h"
#include "ll.h"
#include <string.h>


void ll_s_botstack(CuTest * tc)
{
    const int LOOPS = 10000;
    struct ll * list = ll_new(SINGLE);
    
    for(int i = 0; i < LOOPS; i++){
        int val = i;
        struct ln * node = ll_new_node(&val,sizeof(val),SINGLE);
        
        list->push_back(list, node);
        CuAssertIntEquals(tc, list->length, i+1);
    }

    for(int i = LOOPS; i > 0; i--){
        int val = i;
        struct ln * node = list->pop_back(list);
        CuAssertIntEquals(tc, list->length, i-1);
        ll_delete_node(node);
    }
    
    ll_delete(list);
}


int main(void) { return execute(ll_s_botstack);}