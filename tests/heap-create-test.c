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

void hp_create_test(CuTest * tc)
{
    struct hp * h = hp_new(5,sizeof(int), comp);
    CuAssertIntEquals(tc, 1, h->_index);
    CuAssertIntEquals(tc, sizeof(int), h->_elemsize);
    CuAssertIntEquals(tc, 5, h->_capacity);
    
    hp_delete(h);
}


int main(void) { return execute(hp_create_test);}