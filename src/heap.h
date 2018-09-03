#ifndef __HEAP_H
#define __HEAP_H


struct heap {
    void (*push)(struct heap * self, int value);
    int (*pop)(struct heap * self);
    int (*peek)(struct heap * self);
    int (*print)(struct heap * self);
    int _capacity;
    int _elemsize;
    void * _array;
    int _index;
};

struct heap * heap_new(int capacity, int elemsize);
void heap_delete(struct heap * self);

#endif