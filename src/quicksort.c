#include "quicksort.h"
#include <stddef.h>

static void troca_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* Particao de Lomuto: usa o ultimo elemento como pivo, move os menores
   ou iguais para a esquerda e devolve o indice final do pivo. */
static int particao_int(int *v, int lo, int hi) {
    int pivo = v[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (v[j] <= pivo) {
            i++;
            troca_int(&v[i], &v[j]);
        }
    }
    troca_int(&v[i + 1], &v[hi]);
    return i + 1;
}

static void quicksort_int_rec(int *v, int lo, int hi) {
    if (lo < hi) {
        int p = particao_int(v, lo, hi);
        quicksort_int_rec(v, lo, p - 1);
        quicksort_int_rec(v, p + 1, hi);
    }
}

void quicksort_int(int *v, int n) {
    if (v == NULL || n < 2) return;
    quicksort_int_rec(v, 0, n - 1);
}
