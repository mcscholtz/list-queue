#ifndef LL_H
#define LL_H

//Helper Macros
#define DNEXT(node) (((struct d_link *)node->link)->next)
#define DPREV(node) (((struct d_link *)node->link)->prev)
#define SNEXT(node) (((struct s_link *)node->link)->next)

typedef enum  { SINGLE, DOUBLE } LL_TYPE;

struct ll {
	/* Private Data DO NOT TOUCH */
	struct ln * head;
	struct ln * tail;

	/* Read only. DO NOT MODIFY */
	LL_TYPE type;
	int length;
    
	/* Peek Functions */
	//Returns the pointer to the data of the head
	void * (*front)(struct ll * list);
	//Returns the pointer to the data of the tail
	void * (*back)(struct ll * list);
	//Returns the pointer to the data at the index
	void * (*at)(struct ll * list, int index);
	
	/* Push Functions */
	//Push the node to the front of the list
	void (*push_front)(struct ll * list, struct ln * node);
	//Push the node to the back of the list (very slow for single linked)
	void (*push_back)(struct ll * list, struct ln * node);
	//Push the node behind the given node (slow)
	void (*push_behind)(struct ll * list, struct ln * behind, struct ln * node);
	//Push the node so that it is at the given index, assuming the list is long enough (slow)
	void (*push_at)(struct ll * list, int index, struct ln * node);
	
	/* Pop Functions */
	//Pop the front node
	struct ln * (*pop_front)(struct ll * list);
	//Pop the back node (very slow for single linked)
	struct ln * (*pop_back)(struct ll * list);
	//Pop the node behind the given node (slow)
	struct ln * (*pop_behind)(struct ll * list, struct ln * node);
	//Pop the node at the given index (slow)
	struct ln * (*pop_at)(struct ll * list, int index);

	/* Utility Functions */
	//Apply the given function to each element
	void (*foreach)(struct ll * list, void (*func)(void * element));
};


struct ln {
    void * data;
	void * link;
};

struct s_link {
    struct ln * next;
}; 

struct d_link {
    struct ln * next;
    struct ln * prev;
};  

//Create a new list of the given type (SINGLE/DOUBLE)
struct ll * ll_new(LL_TYPE type);
//Create a new node. The data given is coppied internally and does not depend on the pointer to stay valid
struct ln * ll_new_node(void * data, int length, LL_TYPE type);
//Delete the list and all nodes in it
void ll_delete(struct ll * list);
//Delete the given node
void ll_delete_node(struct ln * node);
#endif