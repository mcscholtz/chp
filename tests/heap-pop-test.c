#include "suite.h"
#include "hp.h"

void hp_pop_test(CuTest * tc)
{
    struct hp * h = hp_new(10,sizeof(int));

    h->push(h,1);
    h->push(h,2);
    h->push(h,3);
    h->push(h,7);
    h->push(h,5);
    h->push(h,4);
    h->push(h,6);
    h->push(h,11);
    h->print(h);
    //printf("--------\n");
    int val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,11,val);
    CuAssertIntEquals(tc,7, h->peek(h));
    
    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,7,val);
    CuAssertIntEquals(tc,6, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,6,val);
    CuAssertIntEquals(tc,5, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,5,val);
    CuAssertIntEquals(tc,4, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,4,val);
    CuAssertIntEquals(tc,3, h->peek(h));

    //printf("push another 3 3's");
    h->push(h,3);
    h->push(h,3);
    h->push(h,3);
   // h->print(h);

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,3,val);
    CuAssertIntEquals(tc,3, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,3,val);
    CuAssertIntEquals(tc,3, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,3,val);
    CuAssertIntEquals(tc,3, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
    //h->print(h);
    CuAssertIntEquals(tc,3,val);
    CuAssertIntEquals(tc,2, h->peek(h));

    //printf("--------\n");
    val = h->pop(h);
   // h->print(h);
    CuAssertIntEquals(tc,2,val);
    CuAssertIntEquals(tc,1, h->peek(h));

    hp_delete(h);
}


int main(void) { return execute(hp_pop_test);}