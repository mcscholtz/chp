#ifndef __HP_P_H
#define __HP_P_H
#include "hp.h"

static void * hp_at(struct heap * self, int index)
{
    return ((char *)self->_array + self->_elemsize*index);
}

#endif