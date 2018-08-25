#include "cutest.h"
#include "ll.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//Constants
const uint32_t LIST_LENGTH = 4096;

//Tests
void PushBackIntegrityTest(CuTest *tc);
void PushBackPopFrontTest(CuTest *tc);
void PushBackPopBackTest(CuTest *tc);

//Internal Functions
struct sll * ConstructByPushBack(CuTest *tc, uint32_t len);

//Construct a list with dummy data
struct sll * ConstructByPushBack(CuTest *tc, uint32_t len)
{
	//create empy list
	struct sll * list = sll_new();
	CuAssertPtrNotNull(tc,list);

	//add dummy data to the list
	struct sll_node * node;
	for(uint32_t i = 0; i < len; i++) {
		uint32_t * data = (uint32_t *)malloc(sizeof(uint32_t));
		*data = i;
		node = sll_new_node(data, sizeof(uint32_t));
		list->insert_back(list, node);
	}

	//validate length
	CuAssertIntEquals(tc, len, list->length);

	return list;
}

//test constructed list data integrity
void PushBackIntegrityTest(CuTest *tc)
{
	struct sll * list = ConstructByPushBack(tc, LIST_LENGTH);
	struct sll_node * node;

	//walk the list to validate it
	node = list->head;
	uint32_t index = 0;
	while(node) {
		CuAssertIntEquals(tc, index, *(uint32_t *)node->data);
		node = node->next;
		index++;
	};

	//delete List
	sll_delete(list);
}

//validate that removing from the front of the list works
void PushBackPopFrontTest(CuTest *tc)
{
	struct sll * list = ConstructByPushBack(tc, LIST_LENGTH);
	struct sll_node * node;

	//walk the list to validate it
	uint32_t index = 0;

	while(index < LIST_LENGTH ) {
		//pop front
		node = list->remove_front(list);
		//validate length
		CuAssertIntEquals(tc, LIST_LENGTH - (index+1), list->length);
		//validate data
		CuAssertIntEquals(tc, index, *(uint32_t *)node->data);
		//free node
		sll_delete_node(node);
		index++;
	};
	
	//list should now be empty
	CuAssertPtrEquals(tc,NULL,list->head);
	CuAssertPtrEquals(tc,NULL,list->tail);
	CuAssertIntEquals(tc, 0, list->length);

	//delete List
	sll_delete(list);
}

//validate that removing from the back of the list works
void PushBackPopBackTest(CuTest *tc)
{
	struct sll * list = ConstructByPushBack(tc, LIST_LENGTH);
	struct sll_node * node;

	//walk the list to validate it
	uint32_t index = 0;

	while(index < LIST_LENGTH) {
		//pop front
		node = list->remove_back(list);
		//validate length
		CuAssertIntEquals(tc, LIST_LENGTH - (index+1), list->length);
		//validate data
		CuAssertIntEquals(tc, LIST_LENGTH - (index+1), *(uint32_t *)node->data);
		//free node
		sll_delete_node(node);
		index++;
	};
	
	//list should now be empty
	CuAssertPtrEquals(tc,NULL,list->head);
	CuAssertPtrEquals(tc,NULL,list->tail);
	CuAssertIntEquals(tc, 0, list->length);

	//delete List
	sll_delete(list);
}

CuSuite* LinkedListSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, PushBackIntegrityTest);
	SUITE_ADD_TEST(suite, PushBackPopFrontTest);
	SUITE_ADD_TEST(suite, PushBackPopBackTest);
	return suite;
}