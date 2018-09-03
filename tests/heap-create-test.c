#include "suite.h"
#include "hp.h"

void hp_create_test(CuTest * tc)
{
    struct hp * h = hp_new(5,sizeof(int));
    CuAssertIntEquals(tc, 1, h->_index);
    CuAssertIntEquals(tc, sizeof(int), h->_elemsize);
    CuAssertIntEquals(tc, 5, h->_capacity);
    
    hp_delete(h);
}


int main(void) { return execute(hp_create_test);}