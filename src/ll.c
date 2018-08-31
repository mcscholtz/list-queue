#include "ll.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

//Internal Functions
static struct ln * ll_find_node_at(struct ll * list, int index);

//Forward Declerations
static void * ll_front(struct ll * list);
static void * ll_back(struct ll * list);
static void * ll_at(struct ll * list, int index);

static void ll_push_front(struct ll * list, struct ln * node);
static struct ln * ll_pop_front(struct ll * list);

static void ll_push_back(struct ll * list, struct ln * node);
static struct ln * ll_pop_back(struct ll * list);

static void ll_push_behind(struct ll * list, struct ln * behind, struct ln * node);
static struct ln * ll_pop_behind(struct ll * list, struct ln * behind);

static void ll_push_at(struct ll * list, int index, struct ln * node);
static struct ln * ll_pop_at(struct ll * list, int index);

static void ll_foreach(struct ll * list, void (*func)(void * element));

struct ll * ll_new(LL_TYPE type)
{
	assert(type != SINGLE || type != DOUBLE);
    struct ll * list = (struct ll*)malloc(sizeof(struct ll));
	assert(list != NULL);
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
    list->type = type;

    list->front = ll_front;
    list->back = ll_back;
    list->at = ll_at;

    list->push_front = ll_push_front;
    list->pop_front = ll_pop_front;

    list->push_back = ll_push_back;
    list->pop_back = ll_pop_back;

    list->push_behind = ll_push_behind;
    list->pop_behind = ll_pop_behind;

    list->push_at = ll_push_at;
    list->pop_at = ll_pop_at;
    
    list->foreach = ll_foreach;

	return list;
}



void ll_delete(struct ll * list)
{
	assert(list->type != SINGLE || list->type != DOUBLE);
    struct ln * node = list->head;
	struct ln * next;
    if(list->type == SINGLE) {
        while (node != NULL) {
            next = ((struct d_link *)node->link)->next;
            next = SNEXT(node);
            SNEXT(node) = NULL;
            ll_delete_node(node);
            node = next;
	    } 
    }else{
        while (node != NULL) {
            next = ((struct d_link *)node->link)->next;
            next = DNEXT(node);
            DNEXT(node) = NULL;
            ll_delete_node(node);
            node = next;
	    }
    }
	free(list);
}

struct ln * ll_new_node(void * data, int length, LL_TYPE type)
{
    assert(type != SINGLE || type != DOUBLE);
    struct ln * node = (struct ln *)malloc(sizeof(struct ln));
    if(type == SINGLE){
        node->link = malloc(sizeof(struct s_link));
        SNEXT(node) = NULL;
    }else{
        node->link = malloc(sizeof(struct d_link));
        DNEXT(node) = NULL;
        DPREV(node) = NULL;
    }

	node->data = malloc(length);
	assert(node->data != NULL);
	memcpy(node->data, data, length);
	return node;
}

void ll_delete_node(struct ln * node) {
	assert(node != NULL);
	assert(node->data != NULL);
    assert(node->link != NULL);
	free(node->data);
    free(node->link);
	free(node);
}

static void * ll_front(struct ll * list)
{
    assert(list != NULL);
    assert(list->length > 0);
    return list->head->data;
}

static void * ll_back(struct ll * list)
{
    assert(list != NULL);
    assert(list->length > 0);
    return list->tail->data;
}

static void * ll_at(struct ll * list, int index)
{
    struct ln * n = ll_find_node_at(list, index);
    return n->data;
}

//This function assumes it gets the right node type
static void ll_push_front(struct ll * list, struct ln * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else if (list->head != NULL) {
		if(list->type == SINGLE){
            SNEXT(node) = list->head;  
        }else{
            DPREV(list->head) = node;
            DNEXT(node) = list->head;
        }
        list->head = node;
	}
	list->length++;
}

static struct ln * ll_pop_front(struct ll * list)
{
	assert(list != NULL);
	
	//empty list
	if (list->head == NULL) {
		return NULL;
	}
	else {
		struct ln * node = list->head;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			if(list->type == SINGLE){
                list->head = SNEXT(node);  
                SNEXT(node) = NULL;
            }else{
                list->head = DNEXT(node); 
                DPREV(list->head) = NULL;
                DNEXT(node) = NULL;
                DPREV(node) = NULL;
            }
		}
		list->length--;
		return node;
	}
}

static void ll_push_back(struct ll * list, struct ln * node)
{
	assert(list != NULL);
	assert(node != NULL);

	if (list->tail == NULL) {
		list->head = node;
	}
	else if (list->tail != NULL) {
        if(list->type == SINGLE){
            SNEXT(list->tail) = node;
        }else{
            DPREV(node) = list->tail;
            DNEXT(list->tail) = node;
        }		
	}
    list->tail = node;
	list->length++;
}

static struct ln * ll_pop_back(struct ll * list)
{
	assert(list != NULL);

	//empty list
	if (list->tail == NULL) {
		return NULL;
	}
	else {
		struct ln * node = list->tail;
		//in the case where there was just 1 item
		if (list->head == list->tail) {
			list->tail = NULL;
			list->head = NULL;
		}
		else {
			struct ln * new_tail = list->head;
			if(list->type == SINGLE){
                //Walk the list to the second from last item (expensive)
                while (SNEXT(new_tail) != list->tail) {
				    new_tail = SNEXT(new_tail);
			    }
                SNEXT(new_tail) = NULL;
                SNEXT(node) = NULL;
            }else{
			    new_tail = DPREV(list->tail);
                DNEXT(new_tail) = NULL;
                DNEXT(node) = NULL;
            }
            list->tail = new_tail;
		}
		list->length--;
		return node;
	}
}

//insert a node behind the givin node
static void ll_push_behind(struct ll * list, struct ln * behind, struct ln * node)
{
	assert(list != NULL);
	assert(behind != NULL);
	assert(node != NULL);

	if(behind == list->tail) {
		ll_push_back(list, node);
        return;
	}
    if(list->type == SINGLE){
        SNEXT(node) = SNEXT(behind);
        SNEXT(behind) = node;
    }else{
        DNEXT(node) = DNEXT(behind);
        DPREV(node) = behind;
        DPREV(DNEXT(behind)) = node;
        DNEXT(behind) = node;
    }
	list->length++;
}

static struct ln * ll_pop_behind(struct ll * list, struct ln * behind)
{
	assert(list != NULL && "The list you are trying to pop from is NULL") ;
	assert(behind != NULL && "The node you are trying to pop from behind is NULL");
	assert(behind != list->tail && "Did you try to pop the item behind the tail?");

	struct ln * node;
    if(list->type == SINGLE){
        node = SNEXT(behind);
        if(node == list->tail) {
		    list->tail = behind;
	    }
        SNEXT(behind) = SNEXT(node);
        SNEXT(node) = NULL;
    }else{
        node = DNEXT(behind);
        if(node == list->tail) {
		    list->tail = behind;
            DNEXT(list->tail) = NULL;
        }else{
            DPREV(DNEXT(node)) = behind;
        }
        DNEXT(behind) = DNEXT(node);
        DNEXT(node) = NULL;
        DPREV(node) = NULL;
    }
	list->length--;

	return node;
}

static void ll_push_at(struct ll * list, int index, struct ln * node)
{
    struct ln * n = ll_find_node_at(list, index-1);
    if(n == list->tail) {
        ll_push_back(list, node);
        return;
    }
    ll_push_behind(list, n, node);
}

static struct ln * ll_pop_at(struct ll * list, int index)
{
    struct ln * n = ll_find_node_at(list, index-1);
    if(n == list->tail) {
        return ll_pop_back(list);
    }
    return ll_pop_behind(list,n);
}

static struct ln * ll_find_node_at(struct ll * list, int index)
{
    assert(list != NULL && "The list you are trying to pop from is NULL") ;
	assert(index < list->length && "The index is out of range");
    struct ln * n;
    if(index == list->length-1){
        printf("tail @ index: %d\n", index);
        n = list->tail;
    }else{
        if(list->type == SINGLE){
            n = list->head;
            //Walk the list to find the node before the index
            for(int i = 0; i < index; i++) {
                n = SNEXT(n);
            }
        }else{
            //check if it is faster to go from back or front
            if(index > list->length/2){
                //go from back
                n = list->tail;
                //Walk the list to the index-1
                for(int i = list->length-1; i > index; i--) {
                    n = DPREV(n);
                }
            }else{
                //go from front
                n = list->head;
                //Walk the list to the index-1
                for(int i = 0; i < index; i++) {
                    n = DNEXT(n);
                }
            }
        }
    }
    return n;
}

static void ll_foreach(struct ll * list, void (*func)(void * element))
{
    struct ln * node = list->head;
    if(list->type == SINGLE){
        while(node != NULL){
            func(node->data);
            node = SNEXT(node);
        }
    }
    else{
        while(node != NULL){
            func(node->data);
            node = DNEXT(node);
        }
    }
}