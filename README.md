# Linked Lists in C
## Build
```bash
git clone --recurse-submodules https://github.com/mcscholtz/cll.git
cd cll
cmake .
make
```
## Run the Tests
`./build/tests`

## Use in your Code
```c
#include "sll.h"
...
struct sll * list = sll_new();
int somedata = 1;
struct sll_node * node = sll_new_node(&somedata, sizeof(somedata));

list->push_back(list, node);
assert(list->length == 1);

node = list->pop_front(list);
assert(list->length == 0);

sll_delete_node(node);
sll_delete(list); //This will also free all items in the list if there are any
```
For more examples see the [tests](https://github.com/mcscholtz/cll/blob/master/tests/ll_suite.c)

The code is made to be as generic as possible. When actually using it I suggest you change the void pointer in the node struct to the data type of your choice, that will remove a lot of boilerplate code and potential errors by avoiding void pointers.

## Todo
- [x] Add singly linked list
- [x] Add tests for single linked list
- [x] Add doubly linked list
- [x] Add tests for doubly linked list
