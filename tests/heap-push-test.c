#include "suite.h"
#include "hp.h"

void hp_push_test(CuTest * tc)
{
    struct heap * h = heap_new(10,sizeof(int));

    h->push(h,1);
    CuAssertIntEquals(tc, 1, h->peek(h));
    
    h->push(h,2);
    CuAssertIntEquals(tc, 2, h->peek(h));
    
    h->push(h,3);
    CuAssertIntEquals(tc, 3, h->peek(h));

    h->push(h,7);
    CuAssertIntEquals(tc, 7, h->peek(h));

    h->push(h,5);
    CuAssertIntEquals(tc, 7, h->peek(h));

    h->push(h,4);
    CuAssertIntEquals(tc, 7, h->peek(h));

    h->push(h,6);
    CuAssertIntEquals(tc, 7, h->peek(h));

    h->push(h,11);
    CuAssertIntEquals(tc, 11, h->peek(h));
    
    h->print(h);
    heap_delete(h);
}


int main(void) { return execute(hp_push_test);}