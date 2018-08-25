#include "cutest.h"
#include "sll.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void CreateList(CuTest *tc) {
	//create empty list
	struct sll * list = sll_new();
	CuAssertPtrNotNull(tc,list);
	CuAssertIntEquals(tc, list->length, 0);
	CuAssertPtrEquals(tc, list->head, list->tail);

	sll_delete(list);
}

void CreateIntNode(CuTest *tc) {
	//create empty node
	int val = 123;
	struct sll_node * node = sll_new_node(&val, sizeof(val));

	CuAssertPtrNotNull(tc, node);
	CuAssertIntEquals(tc, *(int *)node->data, val);
	CuAssertPtrEquals(tc, node->next, NULL);

	sll_delete_node(node);
}

void CreateStringNode(CuTest *tc) {
	//create empty node
	char string[] = "this is a string node";
	struct sll_node * node = sll_new_node(&string, sizeof(string));

	CuAssertPtrNotNull(tc, node);
	CuAssertIntEquals(tc, strcmp(string, (char *)node->data), 0);
	CuAssertPtrEquals(tc, node->next, NULL);
	
	sll_delete_node(node);
}

void PushPopFrontAndBack(CuTest * tc) {
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

void PushPopMiddle(CuTest * tc) {
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

	sll_delete(list);
}

CuSuite* SingleLinkedListSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, CreateList);
	SUITE_ADD_TEST(suite, CreateIntNode);
	SUITE_ADD_TEST(suite, CreateStringNode);
	SUITE_ADD_TEST(suite, PushPopFrontAndBack);
	SUITE_ADD_TEST(suite, PushPopMiddle);

	return suite;
}