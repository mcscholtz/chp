#include "suite.h"
#include "hp.h"

void * comp(void * elem1, void * elem2);

void * comp(void * elem1, void * elem2)
{
    printf("%d > %d\n", *(int*)elem1, *(int*)elem2);
    if(*(int*)elem1 > *(int*)elem2){
        return elem1;
    }else{
        return elem2;
    }
}

void hp_push_test(CuTest * tc)
{
    struct hp * h = hp_new(10,sizeof(int), comp);
    int peek, push;
    
    push = 1;
    h->push(h, &push); 
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 1, peek);
    
    push = 2;
    h->push(h, &push);
    h->peek(h, &peek);
    h->print(h);
    CuAssertIntEquals(tc, 2, peek);
    
    push = 3;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 3, peek);

    push = 7;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 7, peek);

    push = 5;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 7, peek);

    push = 4;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 7, peek);

    push = 6;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 7, peek);

    push = 11;
    h->push(h, &push);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 11, peek);
    
    h->print(h);
    hp_delete(h);
}


int main(void) { return execute(hp_push_test);}