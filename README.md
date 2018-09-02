[![Build Status](https://travis-ci.org/mcscholtz/cll.svg?branch=master)](https://travis-ci.org/mcscholtz/cll)
# Linked Lists in C
## Build
```bash
git clone --recurse-submodules https://github.com/mcscholtz/cll.git
cd cll
cmake .
make
ctest
```
## Use in your Code
```c
#include "ll.h"

struct ll * list = ll_new(DOUBLE); //Create a doubly linked list
int somedata = 1;
struct ln * node = ll_new_node(&somedata, sizeof(somedata)); //internally copy data from somedata
...
//Do stuff with the node and list, see supported opperations below
...
ll_delete_node(node);
ll_delete(list); //This will also free all items in the list if there are any left
```
## Supported opperations
Both the singly and doubly lists support the following oppperations:
### push_front / pop_front
```c
list->push_front(list, node);
struct ln * node2 = list->pop_front(list);
```
### push_back / pop_back
```c
list->push_back(list, node);
struct ln * node2 = list->pop_back(list);
```
### push_behind / pop_behind (Push or pop the node behind the given node)
```c
list->push_behind(list, behind, node);
struct ln * node2 = list->pop_behind(list, node);
```
### push_at / pop_at (Push or pop the node at the given index)
```c
list->push_at(list, 1, node);
struct ln * node2 = list->pop_at(list, 1);
```
## foreach (Apply function to each element in the list function signature: `void func(void * element)`
```c
void add5(void * element)
{
    *(int *)element += 5;
}
...
list->foreach(list,add5); //adds 5 to each element in the list
```
### front / back / at (Directly return the pointer to the data of the requested node)
```c
int * a = (int *)list->front(list);
*a = 123;
int * b = (int *)list->at(list, 0); //At index 0 is the same as front
assert(123 == *b);
...

```
For more examples look at the [tests](https://github.com/mcscholtz/cll/blob/master/tests/)
## TODO
- [ ] Add concat function
- [ ] Add split function
- [ ] Add sort function
