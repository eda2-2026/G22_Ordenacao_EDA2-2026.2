#include "bubblesort.h"
#include <stddef.h>

static void troca_produto(Produto *a, Produto *b) {
    Produto t = *a; *a = *b; *b = t;
}

void bubblesort(Produto *v, int n, Comparador cmp) {
    if (v == NULL || cmp == NULL || n < 2) return;
    for (int fim = n - 1; fim > 0; fim--) {
        int trocou = 0;
        for (int j = 0; j < fim; j++) {
            if (cmp(&v[j], &v[j + 1]) > 0) {
                troca_produto(&v[j], &v[j + 1]);
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}
