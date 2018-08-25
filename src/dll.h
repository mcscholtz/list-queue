#ifndef DLL_H
#define DLL_H

struct dll {
	struct dll_node * head;
	struct dll_node * tail;
	int length;
	void (*push_front)(struct dll *, struct dll_node *);
	void (*push_back)(struct dll *, struct dll_node *);
	void (*push_behind)(struct dll *, struct dll_node *, struct dll_node *);
	struct dll_node * (*pop_front)(struct dll *);
	struct dll_node * (*pop_back)(struct dll *);
	struct dll_node * (*pop_behind)(struct dll *, struct dll_node *);
};

struct dll_node {
	void * data;
	struct dll_node * next;
    struct dll_node * prev;
};

struct dll * dll_new();
struct dll_node * dll_new_node(void * data, int length);
void dll_delete(struct dll * list);
void dll_delete_node(struct dll_node * node);
#endif