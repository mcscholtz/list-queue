#include "suite.h"
#include "ll.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void ll_d_pushat(CuTest * tc)
{
    const int LOOPS = 10000;
    struct ll * list = ll_new(DOUBLE);
    //add nodes
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),DOUBLE);
        if(i < 1){
            list->push_back(list, node);
        }else{
            list->push_at(list, 1, node);
        }
        
        CuAssertIntEquals(tc, list->length, i+1);
    }

    //validate nodes with at function
    for(int i = 0; i < LOOPS; i++){
        if(i < 1){
            int *j = list->at(list,i);
            CuAssertIntEquals(tc, i, *j);
        }else{
            int *j = list->at(list,i);
            CuAssertIntEquals(tc, LOOPS - i, *j);
        }
    }

    ll_delete(list);
}


int main(void) { return execute(ll_d_pushat);}