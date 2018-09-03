#include "suite.h"
#include "hp.h"

void * comp(void * elem1, void * elem2);

void * comp(void * elem1, void * elem2)
{
    if(*(int*)elem1 > *(int*)elem2){
        return elem1;
    }else{
        return elem2;
    }
}


void hp_pop_test(CuTest * tc)
{
    struct hp * h = hp_new(10,sizeof(int), comp);
    int push = 1;
    h->push(h, &push);
    push = 2;
    h->push(h, &push);
    push = 3;
    h->push(h, &push);
    push = 7;
    h->push(h, &push);
    push = 5;
    h->push(h, &push);
    push = 4;
    h->push(h, &push);
    push = 6;
    h->push(h, &push);
    push = 11;
    h->push(h, &push);
   // h->print(h);
    //printf("--------\n");
    int pop, peek;
    h->pop(h, &pop);
    //h->print(h);
    CuAssertIntEquals(tc, 11, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 7, peek);
    
    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,7, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,6, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,6, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,5, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,5, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,4, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,4, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek);

    //printf("push another 3 3's");
    push = 3;
    h->push(h, &push);
    h->push(h, &push);
    h->push(h, &push);
   // h->print(h);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,2, peek);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,2, pop);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,1, peek);

    hp_delete(h);
}


int main(void) { return execute(hp_pop_test);}