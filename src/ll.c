#include "ll.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

//Internal Functions
static void * ll_front(struct ll * list);
static void * ll_back(struct ll * list);
static void * ll_at(struct ll * list, int index);

static void ll_push_front(struct ll * list, struct ln * node);
static struct ln * ll_pop_front(struct ll * list);

static void ll_push_back(struct ll * list, struct ln * node);
static struct ln * ll_pop_back(struct ll * list);

static void ll_push_behind(struct ll * list, struct ln * behind, struct ln * node);
static struct ln * ll_pop_behind(struct ll * list, struct ln * behind);

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
    if(type == SINGLE){
    //    list->push_front = dll_push_front;
    //    list->push_back = dll_push_back;
    //    list->push_behind = dll_push_behind;
    //    list->pop_front = dll_pop_front;
    //    list->pop_back = dll_pop_back;
    //    list->pop_behind = dll_pop_behind;
    }else{
    
    //    list->push_back = dll_push_back;
     //   list->push_behind = dll_push_behind;
    //    list->pop_front = dll_pop_front;
    //    list->pop_back = dll_pop_back;
    //    list->pop_behind = dll_pop_behind;
    }
	
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
    assert(list != NULL);
    assert(index <= list->length);
    if(index == list->length){
        return list->tail->data;
    }
    struct ln * node;
    if(list->type == SINGLE){
        node = list->head;
        //Walk the list to the index
        for(int i = 0; i < index; i++) {
            node = SNEXT(node);
        }
    }else{
        //check if it is faster to go from back or front
        if(index > list->length/2){
            //go from back
            node = list->tail;
            //Walk the list to the index
            for(int i = list->length-1; i > index; i--) {
                node = DPREV(node);
            }
        }else{
            //go from front
            node = list->head;
            //Walk the list to the index
            for(int i = 0; i < index; i++) {
                node = DNEXT(node);
            }
        }
    }
    return node->data;
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

