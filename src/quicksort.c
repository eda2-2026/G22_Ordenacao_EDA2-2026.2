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

/* Pivo mediana-de-tres (Dia 4).
   Ordena v[lo] <= v[mid] <= v[hi] usando no maximo 3 comparacoes e, em
   seguida, move a mediana para v[hi], que e a posicao que a particao de
   Lomuto usa como pivo. Com isso o pior caso O(n^2) deixa de ocorrer em
   vetores ja ordenados ou invertidos (entradas que, com o pivo fixo no
   ultimo elemento, gerariam particoes totalmente desbalanceadas). */
static void mediana_de_tres(Produto *v, int lo, int hi, Comparador cmp) {
    int mid = lo + (hi - lo) / 2;
    if (cmp(&v[mid], &v[lo]) < 0) troca_produto(&v[mid], &v[lo]);
    if (cmp(&v[hi],  &v[lo]) < 0) troca_produto(&v[hi],  &v[lo]);
    if (cmp(&v[hi],  &v[mid]) < 0) troca_produto(&v[hi],  &v[mid]);
    /* Agora v[mid] e a mediana dos tres; move-a para o fim. */
    troca_produto(&v[mid], &v[hi]);
}

/* Particao de Lomuto generica: o pivo e o ultimo elemento e a ordem e
   decidida pelo comparador cmp (mesma logica da versao para int, so
   trocando "v[j] <= pivo" por "cmp(&v[j], &v[hi]) <= 0"). */
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
        /* So vale a pena escolher a mediana quando ha pelo menos 3
           elementos; com 2 a particao ja resolve sozinha. */
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
