#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

//Internal Structures
struct node {
    void * data;
	struct node * next;
};

//Internal Functions
struct node * new_node(void * data, int size);
void delete_node(struct node * n);

//Forward Declerations
static void queue_peek(struct queue * q, void * elem);

static void queue_dequeue(struct queue * q, void * elem);

static void queue_enqueue(struct queue * list, void * elem);

struct queue * queue_new(int elemsize)
{
    struct queue * q = (struct queue*)malloc(sizeof(struct queue));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	q->length = 0;
    q->elemsize = elemsize;

    q->peek = queue_peek;
    q->dequeue = queue_dequeue;
    q->enqueue = queue_enqueue;

	return q;
}

void queue_delete(struct queue * q)
{
	assert(q != NULL && "The queue is NULL");
    struct node * current = q->head;
	struct node * next;
    while (current  != NULL) {
        next = current->next;
        delete_node(current);
        current = next;
    } 
	free(q);
}

struct node * new_node(void * data, int size)
{
    struct node * n = (struct node *)malloc(sizeof(struct node));
    assert(n != NULL && "Out of memory");
    n->data = malloc(size);
    assert(n->data != NULL && "Out of memory");
	memcpy(n->data, data, size);
	return n;
}


void delete_node(struct node * n) {
	assert(n != NULL);
	assert(n->data != NULL);
	free(n->data);
	free(n);
}

static void queue_peek(struct queue * q, void * elem)
{
    assert(q != NULL && "The queue is NULL");
    assert(q->length > 0 && "The queue does not have enough elements");
    memcpy(elem, q->head->data, q->elemsize);
}

static void queue_dequeue(struct queue * q, void * elem)
{
	assert(q != NULL && "The list is NULL");
    assert(q->length > 0 && "The queue does not have enough elements");
	
    struct node * n = q->head;
    //in the case where there was just 1 item
    if (q->head == q->tail) {
        q->tail = NULL;
        q->head = NULL;
    }else{
        q->head = n->next; 
    }
    memcpy(elem, n->data, q->elemsize);
    delete_node(n);
    q->length--;
}

static void queue_enqueue(struct queue * q, void * elem)
{
	assert(q != NULL && "The list is NULL");
	assert(elem != NULL && "The node you are trying to push is NULL");

    struct node * n = new_node(elem, q->elemsize);

	if (q->tail == NULL) {
		q->head = n;
	}
	else if (q->tail != NULL) {
        q->tail->next = n;
	}
    q->tail = n;
	q->length++;
}