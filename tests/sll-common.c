#include "cutest.h"
#include "sll.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SLL_CreateList(CuTest *tc) {
	//create empty list
	struct sll * list = sll_new();
	CuAssertPtrNotNull(tc,list);
	CuAssertIntEquals(tc, list->length, 0);
	CuAssertPtrEquals(tc, list->head, list->tail);

	sll_delete(list);
}

void SLL_CreateIntNode(CuTest *tc) {
	//create empty node
	int val = 123;
	struct sll_node * node = sll_new_node(&val, sizeof(val));

	CuAssertPtrNotNull(tc, node);
	CuAssertIntEquals(tc, *(int *)node->data, val);
	CuAssertPtrEquals(tc, node->next, NULL);

	sll_delete_node(node);
}

void SLL_CreateStringNode(CuTest *tc) {
	//create empty node
	char string[] = "this is a string node";
	struct sll_node * node = sll_new_node(&string, sizeof(string));

	CuAssertPtrNotNull(tc, node);
	CuAssertIntEquals(tc, strcmp(string, (char *)node->data), 0);
	CuAssertPtrEquals(tc, node->next, NULL);
	
	sll_delete_node(node);
}

void SLL_PushPopFrontAndBack(CuTest * tc) {
	//create list
	struct sll * list = sll_new();

	//push some nodes
	struct sll_node * node;
	int val = 111;

	//add node at the front
	node = sll_new_node(&val, sizeof(val));
	list->push_back(list, node);
	CuAssertIntEquals(tc, list->length, 1);
	CuAssertIntEquals(tc, *(int*)list->head->data, 111);
	//these should be no next node
	CuAssertPtrEquals(tc, list->head->next, NULL);
	CuAssertPtrEquals(tc, list->tail->next, NULL);
	//head + tail should be the same
	CuAssertIntEquals(tc, *(int*)list->head->data, *(int*)list->tail->data);

	//add another node to the front
	val = 222;
	node = sll_new_node(&val, sizeof(val));
	list->push_front(list, node);
	CuAssertIntEquals(tc, list->length, 2);
	CuAssertPtrEquals(tc, list->head->next, list->tail);
	CuAssertIntEquals(tc, *(int*)list->head->data, 222);
	CuAssertIntEquals(tc, *(int*)list->tail->data, 111);

	//add a node to the back
	val = 333;
	node = sll_new_node(&val, sizeof(val));
	list->push_back(list, node);
	CuAssertIntEquals(tc, list->length, 3);
	CuAssertIntEquals(tc, *(int*)list->head->data, 222);
	CuAssertIntEquals(tc, *(int*)list->tail->data, 333);

	//remove front
	node = list->pop_front(list);
	CuAssertIntEquals(tc, list->length, 2);
	CuAssertPtrEquals(tc, list->head->next, list->tail);
	CuAssertIntEquals(tc, *(int*)list->head->data, 111);
	CuAssertIntEquals(tc, *(int*)node->data, 222);
	CuAssertPtrEquals(tc, node->next, NULL);
	sll_delete_node(node);

	//remove back
	node = list->pop_back(list);
	CuAssertIntEquals(tc, list->length, 1);
	CuAssertPtrEquals(tc, list->head->next, NULL);
	CuAssertPtrEquals(tc, list->tail->next, NULL);
	CuAssertPtrEquals(tc, list->tail, list->head);
	CuAssertIntEquals(tc, *(int*)node->data, 333);
	CuAssertPtrEquals(tc, node->next, NULL);
	sll_delete_node(node);

	//remove last node
	node = list->pop_back(list);
	CuAssertIntEquals(tc, list->length, 0);
	CuAssertPtrEquals(tc, list->head, NULL);
	CuAssertPtrEquals(tc, list->tail, NULL);
	CuAssertPtrEquals(tc, list->tail, list->head);
	CuAssertIntEquals(tc, *(int*)node->data, 111);
	CuAssertPtrEquals(tc, node->next, NULL);
	sll_delete_node(node);
	sll_delete(list);
}

void SLL_PushPopMiddle(CuTest * tc) {
	//create list
	struct sll * list = sll_new();

	//push some nodes
	struct sll_node * node;
	int val = 111;

	//add node at the front
	node = sll_new_node(&val, sizeof(val));
	list->push_front(list, node);

	val = 222;
	node = sll_new_node(&val, sizeof(val));
	list->push_back(list, node);

	//now push behind
	val = 333;
	node = sll_new_node(&val, sizeof(val));
	list->push_behind(list, list->head, node);
	CuAssertIntEquals(tc, list->length, 3);
	CuAssertIntEquals(tc, *(int*)list->head->next->data, 333);
	CuAssertPtrEquals(tc, list->head->next->next, list->tail);

	//now remove that item again
	node = list->pop_behind(list, list->head);
	CuAssertIntEquals(tc, list->length, 2);
	CuAssertIntEquals(tc, *(int*)node->data, 333);
	CuAssertPtrEquals(tc, node->next, NULL);
	CuAssertPtrEquals(tc, list->head->next, list->tail);
	sll_delete_node(node);

	sll_delete(list);
}

void SLL_Smoke(CuTest * tc){
	const int LOOPS = 10000;
	//randomly add and remove nodes all over the place
	struct sll * list = sll_new();
	int created = 0;
	int deleted = 0;
	srand(time(NULL));   // should only be called once
	for(int i = 0; i < LOOPS; i++){
		int val = rand();
		struct sll_node * node  = sll_new_node(&val, sizeof(val));
		created++;
		int r = rand();
		switch(r % 5){
			case 0:
				list->push_back(list, node);
				break;
			case 1:
				list->push_front(list, node);
				break;
			default:
				{
					if(list->length == 0) {
						i--;
						sll_delete_node(node);
						continue;
					}
					//Find a random node in the list (only select from the top 10 to keep the test fast)
					int k, h;
					do{
						k = rand() + 1;
						h = list->length;
						if(h > 10){
							h = (rand() % 10) + 1;
						}
					}while(k < h);
					k = k % h;
					
					struct sll_node * n = list->head;
					int j;
					for(j = 0; j < k;j++){
						n = n->next;
					}
					//Once we have the random node, insert the new node behind it
					list->push_behind(list, n, node);
					break;
				}
		}
	}
	CuAssertIntEquals(tc, list->length, LOOPS);

	//now randomly delete nodes
	for(int i = 0; i < LOOPS; i++) {
		int val = rand();
		struct sll_node * node;
		int r = rand();
		switch(r % 5){
			case 0:
				node = list->pop_back(list);
				break;
			case 1:
				node = list->pop_front(list);
				break;
			default:
				{
					if(list->length < 10) {
						i--;
						continue;
					}
					//Find a random node in the list
					int k, h;
					do{
						k = rand() + 1;
						h = list->length;
						if(h > 10){
							h = (rand() % 10) + 1;
						}
					}while(k < h);
					k = k % h;

					struct sll_node * n = list->head;
					int j;
					for(j = 0; j < k;j++){
						n = n->next;
					}
					
					if(n == NULL){
						i--;
						continue;
					}else if(n->next == NULL){
						i--;
						continue;
					}

					//Once we have the random node, pop the node behind it
					node = list->pop_behind(list, n);
					break;
				}
		}
		sll_delete_node(node);
		deleted++;
	}
	CuAssertIntEquals(tc, list->length, 0);
	CuAssertIntEquals(tc, created, deleted);
	sll_delete(list);
}