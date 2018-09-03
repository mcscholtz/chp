#include "suite.h"
#include "hp.h"
#include <time.h>

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
    struct hp * h = hp_new(10000,sizeof(int), comp);
    srand(time(NULL));
    //add random numbers to the stack
    for(int i = 0; i < 9999; i++) {
        int push = rand();
        h->push(h, &push);
    }
    //get the mnax value
    int max;
    h->peek(h, &max);

    //pop all elements, they should be getting smaller
    for(int i = 0; i < 9999; i++) {
        int pop;
        h->pop(h, &pop);
        CuAssert(tc, "New values is greater than previous value", max >= pop);
        max = pop;
    }
    int test = -1;
    h->pop(h, &test);
    CuAssertIntEquals(tc, -1, test);

    hp_delete(h);
}


int main(void) { return execute(hp_pop_test);}