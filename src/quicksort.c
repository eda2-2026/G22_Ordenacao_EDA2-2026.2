#include "quicksort.h"
#include <stddef.h>

static void troca_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

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

static void troca_produto(Produto *a, Produto *b) {
    Produto t = *a; *a = *b; *b = t;
}

static void mediana_de_tres(Produto *v, int lo, int hi, Comparador cmp) {
    int mid = lo + (hi - lo) / 2;
    if (cmp(&v[mid], &v[lo]) < 0) troca_produto(&v[mid], &v[lo]);
    if (cmp(&v[hi],  &v[lo]) < 0) troca_produto(&v[hi],  &v[lo]);
    if (cmp(&v[hi],  &v[mid]) < 0) troca_produto(&v[hi],  &v[mid]);
    troca_produto(&v[mid], &v[hi]);
}

static int particao(Produto *v, int lo, int hi, Comparador cmp) {
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (cmp(&v[j], &v[hi]) <= 0) {
            i++;
            troca_produto(&v[i], &v[j]);
        }
    }
    troca_produto(&v[i + 1], &v[hi]);
    return i + 1;
}

static void quicksort_rec(Produto *v, int lo, int hi, Comparador cmp) {
    if (lo < hi) {
        if (hi - lo >= 2) {
            mediana_de_tres(v, lo, hi, cmp);
        }
        int p = particao(v, lo, hi, cmp);
        quicksort_rec(v, lo, p - 1, cmp);
        quicksort_rec(v, p + 1, hi, cmp);
    }
}

void quicksort(Produto *v, int n, Comparador cmp) {
    if (v == NULL || cmp == NULL || n < 2) return;
    quicksort_rec(v, 0, n - 1, cmp);
}
