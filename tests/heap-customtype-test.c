#include "suite.h"
#include "hp.h"
#include <string.h>

struct person {
    char name[64];
    int age;
};

struct person new_person(const char * name, int age)
{
    struct person p;
    p.age = age;
    strcpy(p.name, name);
    return p;
}

void * comp(void * elem1, void * elem2);

void * comp(void * elem1, void * elem2)
{
    struct person * p1 = elem1;
    struct person * p2 = elem2;
   
    if(p1->age > p2->age){
        return elem1;
    }else{
        return elem2;
    }
}


void hp_pop_test(CuTest * tc)
{
    struct hp * h = hp_new(10,sizeof(struct person), comp);
    struct person push = new_person("bob",12);
    h->push(h, &push);
    push = new_person("james", 17);
    h->push(h, &push);
    push = new_person("joe", 16);
    h->push(h, &push);
    push = new_person("ted", 7);
    h->push(h, &push);
    push = new_person("ed", 5);
    h->push(h, &push);
    push = new_person("jack", 11);
    h->push(h, &push);
    push = new_person("randy", 19);
    h->push(h, &push);
    push = new_person("andy", 27);
    h->push(h, &push);
    //h->print(h);
    //printf("--------\n");
    struct person pop, peek;
    h->pop(h, &pop);
    //h->print(h);
    CuAssertIntEquals(tc, 27, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc, 19, peek.age);
    
    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,19, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,17, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,17, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,16, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,16, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,12, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,12, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,11, peek.age);

    //printf("push another 3 3's");
    push = new_person("luke", 3);
    h->push(h, &push);
    h->push(h, &push);
    h->push(h, &push);
   // h->print(h);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,11, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,7, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,7, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,5, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,5, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek.age);

    //printf("--------\n");
    h->pop(h, &pop);
    CuAssertIntEquals(tc,3, pop.age);
    h->peek(h, &peek);
    CuAssertIntEquals(tc,3, peek.age);

    hp_delete(h);
}


int main(void) { return execute(hp_pop_test);}