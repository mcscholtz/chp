#include "suite.h"
#include "heap.h"

void heap_create_test(CuTest * tc)
{
    struct heap * h = heap_new(5,sizeof(int));
    CuAssertIntEquals(tc, 1, h->_index);
    CuAssertIntEquals(tc, sizeof(int), h->_elemsize);
    CuAssertIntEquals(tc, 5, h->_capacity);
    
    heap_delete(h);
}


int main(void) { return execute(heap_create_test);}