#ifndef LL_H
#define LL_H

struct sll {
	struct sll_node * head;
	struct sll_node * tail;
	int length;
	void (*insert_front)(struct sll *, struct sll_node *);
	void (*insert_back)(struct sll *, struct sll_node *);
	struct sll_node * (*remove_front)(struct sll *);
	struct sll_node * (*remove_back)(struct sll *);
};

struct sll_node {
	void * data;
	struct sll_node * next;
};

struct sll * sll_new();
struct sll_node * sll_node_new(void * data, int length);
void sll_delete(struct sll * list);
void sll_node_delete(struct sll_node * node);
#endif