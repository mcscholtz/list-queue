#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "dll.h"

//Internal functions
static void dll_push_front(struct dll * list, struct dll_node * node);
static void dll_push_back(struct dll * list, struct dll_node * node);
static void dll_push_behind(struct dll * list, struct dll_node * behind, struct dll_node * node);
static struct dll_node * dll_pop_front(struct dll * list);
static struct dll_node * dll_pop_back(struct dll * list);
static struct dll_node * dll_pop_behind(struct dll * list, struct dll_node * behind);

struct dll * dll_new()
{
	struct dll * list = (struct dll*)malloc(sizeof(struct dll));
	assert(list != NULL);
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	list->push_front = dll_push_front;
	list->push_back = dll_push_back;
	list->push_behind = dll_push_behind;
	list->pop_front = dll_pop_front;
	list->pop_back = dll_pop_back;
	list->pop_behind = dll_pop_behind;
	return list;
}

void dll_delete(struct dll * list)
{
	struct dll_node * node = list->head;
	struct dll_node * next;
	while (node != NULL) {
		next = node->next;
		node->next = NULL;
		dll_delete_node(node);
		node = next;
	} 
}

struct dll_node * dll_new_node(void * data, int length)
{
	struct dll_node * node = (struct dll_node *)malloc(sizeof(struct dll));
	node->next = NULL;
    node->prev = NULL;
	node->data = malloc(length);
	assert(node->data != NULL);
	memcpy(node->data, data, length);
	return node;
}

void dll_delete_node(struct dll_node * node) {
	assert(node != NULL);
	assert(node->data != NULL);
	free(node->data);
	free(node);
}

static void dll_push_front(struct dll * list, struct dll_node * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else if (list->head != NULL) {
		node->next = list->head;
        list->head->prev = node;
		list->head = node;
	}
	list->length++;
}

static void dll_push_back(struct dll * list, struct dll_node * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
	}
	else if (list->tail != NULL) {
        node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;		
	}
	list->length++;
}

//insert a node behind the givin node
static void dll_push_behind(struct dll * list, struct dll_node * behind, struct dll_node * node)
{
	assert(list != NULL);
	assert(behind != NULL);
	assert(node != NULL);

	if(behind == list->tail) {
		return dll_push_back(list, node);
	}
	node->next = behind->next;
    node->prev = behind;
    behind->next->prev = node;
	behind->next = node;
	list->length++;
}

static struct dll_node * dll_pop_front(struct dll * list)
{
	assert(list != NULL);
	
	//empty list
	if (list->head == NULL) {
		return NULL;
	}
	else {
		struct dll_node * node = list->head;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			list->head = node->next;
            list->head->prev = NULL;
		}
		list->length--;
		//reduce change to have acidental modification of items in the list
		node->next = NULL;
        node->prev = NULL;
		return node;
	}
}

//this is slow because there is only a single link
static struct dll_node * dll_pop_back(struct dll * list)
{
	assert(list != NULL);

	//empty list
	if (list->tail == NULL) {
		return NULL;
	}
	else {
		struct dll_node * node = list->tail;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			struct dll_node * new_tail = list->tail->prev;
			list->tail = new_tail;
			new_tail->next = NULL;
		}
		list->length--;
		//reduce change to have acidental modification of items in the list
		node->next = NULL;
        node->prev = NULL;
		return node;
	}
}

//return the node behind the given node
static struct dll_node * dll_pop_behind(struct dll * list, struct dll_node * behind)
{
	assert(list != NULL);
	assert(behind != NULL);
	assert(behind->next != NULL && "Did you try to pop the item behind the tail?");

	struct dll_node * node = behind->next;
	if(node == list->tail) {
		list->tail = behind;
        list->tail->next = NULL;
	}else{
        node->next->prev = behind;
    }

	behind->next = node->next; //should be null in the above case that it is the tail
	list->length--;
	//reduce change to have acidental modification of items in the list
	node->next = NULL;
    node->prev = NULL;
	return node;
}