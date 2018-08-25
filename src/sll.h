#ifndef SLL_H
#define SLL_H

struct sll {
	struct sll_node * head;
	struct sll_node * tail;
	int length;
	void (*push_front)(struct sll *, struct sll_node *);
	void (*push_back)(struct sll *, struct sll_node *);
	void (*push_behind)(struct sll *, struct sll_node *, struct sll_node *);
	struct sll_node * (*pop_front)(struct sll *);
	struct sll_node * (*pop_back)(struct sll *);
	struct sll_node * (*pop_behind)(struct sll *, struct sll_node *);
};

struct sll_node {
	void * data;
	struct sll_node * next;
};

struct sll * sll_new();
struct sll_node * sll_new_node(void * data, int length);
void sll_delete(struct sll * list);
void sll_delete_node(struct sll_node * node);
#endif