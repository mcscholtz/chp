#include "heap.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void heap_push(struct heap * self, int value);
int heap_peek(struct heap * self);
void heap_print(struct heap * self);
int heap_pop(struct heap * self);

//Internal
void heap_balance_bottom_up(struct heap * self, int index);
void heap_balance_top_down(struct heap * self, int index);
void heap_swap(struct heap * self, int index1, int index2);
void * heap_at(struct heap * self, int index);
int heap_subnode(struct heap * self, int index);

struct heap * heap_new(int capacity, int elemsize)
{
    struct heap * self = malloc(sizeof(struct heap));
    assert(self != NULL && "Out of memory");
    self->_elemsize = elemsize;
    self->_capacity = capacity;
    self->_array = malloc(capacity*elemsize);
    assert(self->_array != NULL && "Out of memory");
    self->_index = 1;

    self->push = heap_push;
    self->peek = heap_peek;
    self->print = heap_print;
    self->pop = heap_pop;
    return self;
}

void heap_delete(struct heap * self)
{
    assert(self != NULL && "The heap is NULL");
    assert(self->_array != NULL && "The heap has no memory allocated");

    free(self->_array);
    free(self);
}

void heap_push(struct heap * self, int value)
{
    assert(self != NULL && "The heap is NULL");
    assert(self->_index + 1 <= self->_capacity && "Heap is full");

    memcpy((char *)self->_array + self->_elemsize*self->_index,&value,self->_elemsize);
    

    //then balance heap
    heap_balance_bottom_up(self, self->_index);
    self->_index++;
    return;
}

int heap_pop(struct heap * self)
{
    int top = *(int *)((char *)self->_array + self->_elemsize*1);
    //int last = *(int *)((char *)self->_array + self->_elemsize*(self->_index-1));
    //remove topp item.

    //replace top item with last item.
    memcpy(heap_at(self, 1),heap_at(self, self->_index-1),self->_elemsize);
    self->_index--;
    //recursivly balance heap from the 
    heap_balance_top_down(self, 1);
    return top;
}

int heap_peek(struct heap * self)
{
    assert(self != NULL && "The heap is NULL");
    int head;
    memcpy(&head,(char *)self->_array + self->_elemsize*1,self->_elemsize);
    return head;
}

//top down
void heap_balance_bottom_up(struct heap * self, int index)
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
        heap_swap(self, index, p);
    }
    heap_balance_bottom_up(self, index-1);
}

void heap_balance_top_down(struct heap * self, int index)
{
    switch(heap_subnode(self, index))
    {
        case 0: //left
         //   printf("left node\n");
            heap_swap(self, index, index*2);
            heap_balance_top_down(self, index*2);
            break;
        case 1: //right
        //    printf("right node\n");
            heap_swap(self, index, index*2+1);
            heap_balance_top_down(self, index*2+1);
            break;
        default:
         //   printf("last node\n");
            break;
    }      
}

int heap_subnode(struct heap * self, int index)
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
void heap_swap(struct heap * self, int index1, int index2)
{
    //Use index 0 as tmp copy space
    memcpy((char *)self->_array + self->_elemsize*0,heap_at(self, index1),self->_elemsize);
    memcpy(heap_at(self, index1),heap_at(self, index2),self->_elemsize);
    memcpy(heap_at(self, index2),(char *)self->_array + self->_elemsize*0,self->_elemsize);
}

//TODO: Make inline function
void * heap_at(struct heap * self, int index)
{
    return ((char *)self->_array + self->_elemsize*index);
}

/* For debugging only */
void heap_print(struct heap * self)
{
    //print all the data in the heap
    for(int i = 1; i < self->_index; i++)
    {
        printf("[%d]->%d\n", i, *(int *)((char *)self->_array + self->_elemsize*i));
    }
}