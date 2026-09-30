#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "produto.h"

/* Comparador entre dois produtos, no estilo qsort:
   retorna <0 se a vem antes de b, 0 se equivalem, >0 se a vem depois. */
typedef int (*Comparador)(const Produto *a, const Produto *b);

/* Ordena o vetor v de n produtos com Quick Sort, segundo o comparador cmp. */
void quicksort(Produto *v, int n, Comparador cmp);

#endif /* QUICKSORT_H */
