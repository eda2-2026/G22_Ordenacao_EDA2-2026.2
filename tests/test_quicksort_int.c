#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

static int esta_ordenado(const int *v, int n) {
    for (int i = 1; i < n; i++)
        if (v[i - 1] > v[i]) return 0;
    return 1;
}

static int total = 0, falhas = 0;

static void checa(const char *rotulo, int *v, int n) {
    total++;
    quicksort_int(v, n);
    if (esta_ordenado(v, n)) {
        printf("  [ok]     %-26s (n=%d)\n", rotulo, n);
    } else {
        falhas++;
        printf("  [FALHOU] %-26s (n=%d)\n", rotulo, n);
    }
}

int main(void) {
    printf("== Validacao manual do quicksort_int ==\n\n");

    int vazio[1];
    checa("vetor vazio", vazio, 0);

    int um[] = { 42 };
    checa("um elemento", um, 1);

    int ordenado[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    checa("ja ordenado", ordenado, 10);

    int invertido[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    checa("invertido", invertido, 10);

    int iguais[] = { 7, 7, 7, 7, 7, 7 };
    checa("todos iguais", iguais, 6);

    int misto[] = { 3, -1, 0, -5, 2, -5, 9, 0 };
    checa("negativos e repetidos", misto, 8);

    int n = 1000;
    int *aleat = malloc(n * sizeof *aleat);
    srand(42);
    for (int i = 0; i < n; i++) aleat[i] = rand() % 10000;
    checa("aleatorio grande", aleat, n);
    free(aleat);

    printf("\n== Resumo: %d/%d passaram ==\n", total - falhas, total);
    if (falhas > 0) {
        printf("RESULTADO: FALHOU (%d com erro)\n", falhas);
        return 1;
    }
    printf("RESULTADO: SUCESSO (quicksort_int ordena corretamente)\n");
    return 0;
}
