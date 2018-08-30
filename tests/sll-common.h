#ifndef SLL_COMMON_H
#define SLL_COMMON_H
#include "cutest.h"

/* Add all sll unit tests here */
void SLL_CreateList(CuTest *tc);
void SLL_CreateIntNode(CuTest *tc);
void SLL_CreateStringNode(CuTest *tc);
void SLL_PushPopFrontAndBack(CuTest * tc);
void SLL_PushPopMiddle(CuTest * tc);
void SLL_Smoke(CuTest * tc);

#endif