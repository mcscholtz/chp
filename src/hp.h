#ifndef __HP_H
#define __HP_H

#define HEAP_ASSERTION 0

struct hp {
    void (*push)(struct hp * self, void * elem);
    void (*pop)(struct hp * self, void * head);
    void (*peek)(struct hp * self, void * head);
    void * (*compare)(void * elem1, void * elem2);
    int _capacity;
    int _elemsize;
    void * _array;
    int _index;
};

struct hp * hp_new(int capacity, int elemsize, void * (*compare)(void * elem1, void * elem2));
void hp_delete(struct hp * self);

#endif