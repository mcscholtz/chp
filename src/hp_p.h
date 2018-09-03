#ifndef __HP_P_H
#define __HP_P_H
#include "hp.h"

#define ELEM(self, index) ((char *)self->_array + self->_elemsize*(index))

static void * hp_at(struct hp * self, int index)
{
    return ((char *)self->_array + self->_elemsize*index);
}

#endif