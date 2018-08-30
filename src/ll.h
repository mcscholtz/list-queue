#ifndef LL_H
#define LL_H

//Helper Macros
#define DNEXT(node) (((struct d_link *)node->link)->next)
#define DPREV(node) (((struct d_link *)node->link)->prev)
#define SNEXT(node) (((struct s_link *)node->link)->next)

typedef enum  { SINGLE, DOUBLE } LL_TYPE;

struct ll {
	struct ln * head;
	struct ln * tail;
	int length;
    LL_TYPE type;
	void (*push_front)(struct ll * list, struct ln * node);
	void (*push_back)(struct ll * list, struct ln * node);
	void (*push_behind)(struct ll * list, struct ln * behind, struct ln * node);
	struct ln * (*pop_front)(struct ll * list);
	struct ln * (*pop_back)(struct ll * list);
	struct ln * (*pop_behind)(struct ll * list, struct ln * node);
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

struct ll * ll_new(LL_TYPE type);
struct ln * ll_new_node(void * data, int length, LL_TYPE type);
void ll_delete(struct ll * list);
void ll_delete_node(struct ln * node);
#endif