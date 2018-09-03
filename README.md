[![Build Status](https://travis-ci.org/mcscholtz/chp.svg?branch=master)](https://travis-ci.org/mcscholtz/chp)
# A Heap in C
## Build
```bash
git clone --recurse-submodules https://github.com/mcscholtz/chp.git
cd cll
cmake .
make
ctest
```
## Use in your Code
```c
#include "hp.h"

//custom compare function to make the heap work on any data, just return the element that is greater
void * max_int(void * elem1, void * elem2)
{
    if(*(int*)elem1 > *(int*)elem2){
        return elem1;
    }else{
        return elem2;
    }
}

struct hp * h = hp_new(10,sizeof(int), max_int); //heap with 9 slots (n-1)
int data = 1;
h->push(h, &data);
data = 2;
h->push(h, &data);
int max;
h->peek(h, &max);
assert(max == 2);
int ret;
h->pop(h, &ret);
...
hp_delete(h);
```
