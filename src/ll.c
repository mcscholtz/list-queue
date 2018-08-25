#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ll.h"

//Internal functions
static void sll_insert_front(struct sll * list, struct sll_node * node);
static void sll_insert_back(struct sll * list, struct sll_node * node);
static struct sll_node * sll_remove_front(struct sll * list);
static struct sll_node * sll_remove_back(struct sll * list);

struct sll * sll_new()
{
	struct sll * list = (struct sll*)malloc(sizeof(struct sll));
	assert(list != NULL);
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	list->insert_front = sll_insert_front;
	list->insert_back = sll_insert_back;
	list->remove_front = sll_remove_front;
	list->remove_back = sll_remove_back;
	return list;
}

void sll_delete(struct sll * list)
{
	struct sll_node * node = list->head;
	struct sll_node * next;
	while (node != NULL) {
		next = node->next;
		node->next = NULL;
		sll_delete_node(node);
		node = next;
	} 
}

struct sll_node * sll_new_node(void * data, int length)
{
	struct sll_node * node = (struct sll_node *)malloc(sizeof(struct sll));
	node->next = NULL;
	node->data = malloc(length);
	assert(node->data != NULL);
	memcpy(node->data, data, length);
	return node;
}

void sll_delete_node(struct sll_node * node) {
	assert(node != NULL);
	assert(node->data != NULL);
	free(node->data);
	free(node);
}

static void sll_insert_front(struct sll * list, struct sll_node * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else if (list->head != NULL) {
		node->next = list->head;
		list->head = node;
	}
	list->length++;
}

static void sll_insert_back(struct sll * list, struct sll_node * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
	}
	else if (list->tail != NULL) {
		list->tail->next = node;
		list->tail = node;		
	}
	list->length++;
}

//insert a node anywhere
static void sll_insert_index(struct sll * list, struct sll_node * node, int index)
{
	//insert @ a specific index
}

static struct sll_node * sll_remove_front(struct sll * list)
{
	assert(list != NULL);
	
	//empty list
	if (list->head == NULL) {
		return NULL;
	}
	else {
		struct sll_node * node = list->head;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			list->head = node->next;
		}
		list->length--;
		return node;
	}
}

//this is slow because there is only a single link
static struct sll_node * sll_remove_back(struct sll * list)
{
	assert(list != NULL);

	//empty list
	if (list->tail == NULL) {
		return NULL;
	}
	else {
		struct sll_node * node = list->tail;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			//Walk the list to the second from last item
			struct sll_node * new_tail = list->head;
			while (new_tail->next != list->tail) {
				new_tail = new_tail->next;
			}
			list->tail = new_tail;
			new_tail->next = NULL;
		}
		list->length--;
		return node;
	}
}

//remove any node
static void sll_remove_index(struct sll * list, struct sll_node * node, int index)
{
	//remove @ a specific index
}