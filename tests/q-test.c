#include "suite.h"
#include "queue.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

void q_create_test(CuTest * tc)
{
    const int LOOPS = 10000;
    struct queue * q = queue_new(sizeof(int));
    //add nodes
    for(int i = 0; i < LOOPS; i++){
        q->enqueue(q, &i);
        CuAssertIntEquals(tc, q->length, i+1);
        int peek;
        q->peek(q,&peek);
        CuAssertIntEquals(tc, 0, peek);
    }

    //Dequeue
    for(int i = 0; i < LOOPS; i++){
        int dequeue;
        q->dequeue(q,&dequeue);
        CuAssertIntEquals(tc, i, dequeue);
    }

    queue_delete(q);
}


int main(void) { return execute(q_create_test);}