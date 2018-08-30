#include "suite.h"
#include "ll.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void ll_s_list(CuTest * tc)
{
    const int LOOPS = 10000;
    struct ll * list = ll_new(SINGLE);
    
    //Init random seed generator
    srand(time(NULL));
    
    //populate list
    for(int i = 0; i < LOOPS; i++){
        struct ln * node = ll_new_node(&i,sizeof(i),SINGLE);
        int r1,r2;
        if(list->length > 2) {
            r1 = rand() % 3;
        }else{
            r1 = rand() % 2;
        }
         
		switch(r1){
            case 0:
                list->push_back(list, node);
                CuAssertIntEquals(tc, list->length, i+1);
                break;
            case 1:
                list->push_front(list, node);
                CuAssertIntEquals(tc, list->length, i+1);
                break;
            default:
                //get a random number of iterations
                if(list->length > 100) {
                    r2 = (rand() % 99) + 1;
                }else{
                    r2 = (rand() % list->length - 2) + 1;
                }

                //TODO: (MAKE this a function) get the node @ that index
                struct ln * r_node = list->head;
                for(int j = 0; j < r2; j++) {
                    r_node = DNEXT(r_node);
                }

                list->push_behind(list,r_node, node);
                CuAssertIntEquals(tc, list->length, i+1);
                break;
        }
    }
    CuAssertIntEquals(tc, list->length, LOOPS);

    //remove items
    for(int i = LOOPS; i > 0; i--){
        struct ln * node;
        int r1,r2;
        if(list->length > 5) {
            r1 = rand() % 3;
        }else{
            r1 = rand() % 2;
        }

		switch(r1){
            case 0:
                node = list->pop_back(list);
                CuAssertIntEquals(tc, list->length, i-1);
                break;
            case 1:
                node = list->pop_front(list);
                CuAssertIntEquals(tc, list->length, i-1);
                break;
            default:
                //get a random number of iterations
                if(list->length > 100) {
                    r2 = (rand() % 99) + 1;
                }else{
                    r2 = (rand() % list->length - 2) + 1;
                }

                //TODO: (MAKE this a function) get the node @ that index
                struct ln * r_node = list->head;
                for(int j = 0; j < r2; j++) {
                    r_node = DNEXT(r_node);
                }

                node = list->pop_behind(list, r_node);
                CuAssertIntEquals(tc, list->length, i-1);
                break;
        }
        ll_delete_node(node);
    }

    CuAssertIntEquals(tc, list->length, 0);
    ll_delete(list);
}


int main(void) { return execute(ll_s_list);}