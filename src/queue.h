#ifndef QUEUE_H
#define QUEUE_H

struct queue {
	/* Private Data DO NOT TOUCH */
	struct node * head;
	struct node * tail;

	/* Read only. DO NOT MODIFY */
	int length;
	int elemsize;
    
	/* Peek Functions */
	//Returns the pointer to the data of the head
	void (*peek)(struct queue * q, void * elem);
	
	/* Push Functions */
	//Push the node to the front of the list
	void (*enqueue)(struct queue * q, void * elem);
	
	/* Pop Functions */
	void (*dequeue)(struct queue * q, void * elem);
};

//Create a new list of the given
struct queue * queue_new(int elemsize);
//Delete the list and all nodes in it
void queue_delete(struct queue * q);
#endif