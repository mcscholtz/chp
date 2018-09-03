#ifndef __HP_H
#define __HP_H


struct hp {
    void (*push)(struct hp * self, int value);
    int (*pop)(struct hp * self);
    int (*peek)(struct hp * self);
    int (*print)(struct hp * self);
    int _capacity;
    int _elemsize;
    void * _array;
    int _index;
};

struct hp * hp_new(int capacity, int elemsize);
void hp_delete(struct hp * self);

#endif