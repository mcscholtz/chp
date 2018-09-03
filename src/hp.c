#include "hp.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void hp_push(struct hp * self, void * elem);
void hp_peek(struct hp * self, void * head);
void hp_print(struct hp * self);
void hp_pop(struct hp * self, void * head);

//Internal
#define ELEM(self, index) ((char *)self->_array + self->_elemsize*(index))
void hp_balance_bottom_up(struct hp * self, int index);
void hp_balance_top_down(struct hp * self, int index);
void hp_swap(struct hp * self, int index1, int index2);
int hp_select_subnode(struct hp * self, int index);

struct hp * hp_new(int capacity, int elemsize, void * (*compare)(void * elem1, void * elem2))
{
    struct hp * self = malloc(sizeof(struct hp));
    assert(self != NULL && "Out of memory");
    self->_elemsize = elemsize;
    self->_capacity = capacity;
    self->_array = malloc(capacity*elemsize);
    assert(self->_array != NULL && "Out of memory");
    self->_index = 1;

    self->push = hp_push;
    self->peek = hp_peek;
    self->pop = hp_pop;
    self->compare = compare;
    return self;
}

void hp_delete(struct hp * self)
{
    #ifdef HEAP_ASSERTION
        assert(self != NULL && "The heap is NULL");
        assert(self->_array != NULL && "The heap has no memory allocated");
    #endif
    free(self->_array);
    free(self);
}

void hp_push(struct hp * self, void * elem)
{
    #ifdef HEAP_ASSERTION
        assert(self != NULL && "The heap is NULL");
        assert(self->_index + 1 <= self->_capacity && "The heap is full");
    #endif
    //add node at the bottom of the tree
    memcpy(ELEM(self,self->_index), elem, self->_elemsize);
    
    //then balance the tree recursively
    hp_balance_bottom_up(self, self->_index);
    self->_index++;
    return;
}

void hp_pop(struct hp * self, void * head)
{
    #ifdef HEAP_ASSERTION
        assert(self != NULL && "The heap is NULL");
        assert(self->_index != 1 && "The heap is empty");
    #endif
    if(self->_index == 1){
        return;
    }
    //get the head
    memcpy(head, ELEM(self,1), self->_elemsize);

    //replace top item with last item
    memcpy(ELEM(self, 1),ELEM(self, self->_index-1),self->_elemsize);
    self->_index--;
    
    //recursively balance the tree from the top down
    hp_balance_top_down(self, 1);
}

void hp_peek(struct hp * self, void * head)
{
    #ifdef HEAP_ASSERTION
        assert(self != NULL && "The heap is NULL");
    #endif
    memcpy(head, ELEM(self,1), self->_elemsize);
}

//top down
void hp_balance_bottom_up(struct hp * self, int index)
{
    //reached the top of the tree
    if(index == 1) return;

    int p = (int)floor(index/2);

    //call custom compare function, the node returned will be the one passed up the tree
    void * greater = self->compare(ELEM(self, index), ELEM(self,p));
    
    //if the greater pointer is not the same as the current pointer, switch them
    if(greater == ELEM(self, index)){
        hp_swap(self, index, p);
    }

    //balance the tree from the bottom up
    hp_balance_bottom_up(self, index-1);
}

void hp_balance_top_down(struct hp * self, int index)
{
    switch(hp_select_subnode(self, index))
    {
        case 0: //left
            hp_swap(self, index, index*2);
            hp_balance_top_down(self, index*2);
            break;
        case 1: //right
            hp_swap(self, index, index*2+1);
            hp_balance_top_down(self, index*2+1);
            break;
        default:
            break;
    }      
}

int hp_select_subnode(struct hp * self, int index)
{
    int left = index*2;

    if(left > self->_index){
        //no sub nodes
        return -1;
    }

    if(left + 1 > self->_index){
        //there is no right node, only need to check left
        void * greater = self->compare(ELEM(self,left), ELEM(self, index));
        if(greater == ELEM(self,left)){
            return 0;
        }else{
            return -1;
        } 
    }else{
        //check both
        void * greater = self->compare(ELEM(self,left), ELEM(self, (left+1)));
        if(greater == ELEM(self,left)){
            greater = self->compare(ELEM(self,left), ELEM(self, index));
            if(greater == ELEM(self,left)){
                return 0;
            }else{
                return -1;
            }
        }else{
            greater = self->compare(ELEM(self,(left+1)), ELEM(self, index));
            if(greater == ELEM(self,(left+1))){
                return 1;
            }else{
                return -1;
            }
        }
    }
}

//switch the values of index 1 and 2
void hp_swap(struct hp * self, int index1, int index2)
{
    //Use index 0 as tmp copy space since it is already the correct size and won't cost an allocation
    memcpy(ELEM(self, 0), ELEM(self, index1), self->_elemsize);
    memcpy(ELEM(self, index1), ELEM(self, index2), self->_elemsize);
    memcpy(ELEM(self, index2), ELEM(self, 0), self->_elemsize);
}