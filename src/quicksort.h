#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "produto.h"

typedef int (*Comparador)(const Produto *a, const Produto *b);

void quicksort(Produto *v, int n, Comparador cmp);

void quicksort_int(int *v, int n);

#endif
