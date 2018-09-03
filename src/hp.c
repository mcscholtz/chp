#include "hp_p.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void hp_push(struct hp * self, int value);
int hp_peek(struct hp * self);
void hp_print(struct hp * self);
int hp_pop(struct hp * self);

//Internal
void hp_balance_bottom_up(struct hp * self, int index);
void hp_balance_top_down(struct hp * self, int index);
void hp_swap(struct hp * self, int index1, int index2);
int hp_subnode(struct hp * self, int index);

struct hp * hp_new(int capacity, int elemsize)
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
    self->print = hp_print;
    self->pop = hp_pop;
    return self;
}

void hp_delete(struct hp * self)
{
    assert(self != NULL && "The hp is NULL");
    assert(self->_array != NULL && "The hp has no memory allocated");

    free(self->_array);
    free(self);
}

void hp_push(struct hp * self, int value)
{
    assert(self != NULL && "The hp is NULL");
    assert(self->_index + 1 <= self->_capacity && "hp is full");

    memcpy((char *)self->_array + self->_elemsize*self->_index,&value,self->_elemsize);
    

    //then balance hp
    hp_balance_bottom_up(self, self->_index);
    self->_index++;
    return;
}

int hp_pop(struct hp * self)
{
    int top = *(int *)((char *)self->_array + self->_elemsize*1);
    //int last = *(int *)((char *)self->_array + self->_elemsize*(self->_index-1));
    //remove topp item.

    //replace top item with last item.
    memcpy(hp_at(self, 1),hp_at(self, self->_index-1),self->_elemsize);
    self->_index--;
    //recursivly balance hp from the 
    hp_balance_top_down(self, 1);
    return top;
}

int hp_peek(struct hp * self)
{
    assert(self != NULL && "The hp is NULL");
    int head;
    memcpy(&head,(char *)self->_array + self->_elemsize*1,self->_elemsize);
    return head;
}

//top down
void hp_balance_bottom_up(struct hp * self, int index)
{
    if(index == 1) return;

    //start at the last node and work our way up
  //  #define PARENT_INDEX(index) (floor(index/2))
    int p = floor(index/2);
    int val = *(int *)((char *)self->_array + self->_elemsize*index);
    int pval = *(int *)((char *)self->_array + self->_elemsize*p);
    //printf("val: %d, pval: %d\n",val, pval);
    
    //TODO: replace this with a function pointer to a comparison function
    if(val > pval){
        hp_swap(self, index, p);
    }
    hp_balance_bottom_up(self, index-1);
}

void hp_balance_top_down(struct hp * self, int index)
{
    switch(hp_subnode(self, index))
    {
        case 0: //left
         //   printf("left node\n");
            hp_swap(self, index, index*2);
            hp_balance_top_down(self, index*2);
            break;
        case 1: //right
        //    printf("right node\n");
            hp_swap(self, index, index*2+1);
            hp_balance_top_down(self, index*2+1);
            break;
        default:
         //   printf("last node\n");
            break;
    }      
}

int hp_subnode(struct hp * self, int index)
{
    int left = index*2;

    if(left > self->_index){
        //no sub nodes
        return -1;
    }

    int val = *(int *)((char *)self->_array + self->_elemsize*index);
    int left_val = *(int *)((char *)self->_array + self->_elemsize*left);
   // printf("current: %d\n", val);
   // printf("left: %d\n", left_val);
    if(left + 1 > self->_index){
        //there is no right node, only need to check left
        if(left_val > val){
            return 0;
        }else{
            return -1;
        } 
    }else{
        //check both
        int right_val = *(int *)((char *)self->_array + self->_elemsize*(left+1));
     //   printf("right: %d\n", right_val);
        if(left_val > right_val){
            if(left_val > val){
                return 0;
            }else{
                return -1;
            }
        }else{
            if(right_val > val){
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
    //Use index 0 as tmp copy space
    memcpy((char *)self->_array + self->_elemsize*0,hp_at(self, index1),self->_elemsize);
    memcpy(hp_at(self, index1),hp_at(self, index2),self->_elemsize);
    memcpy(hp_at(self, index2),(char *)self->_array + self->_elemsize*0,self->_elemsize);
}

/* For debugging only */
void hp_print(struct hp * self)
{
    //print all the data in the hp
    for(int i = 1; i < self->_index; i++)
    {
        printf("[%d]->%d\n", i, *(int *)((char *)self->_array + self->_elemsize*i));
    }
}