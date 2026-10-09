#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"
#include "comparadores.h"
#include "quicksort.h"
#include "bubblesort.h"

#define LIMIAR_CLOCKS (CLOCKS_PER_SEC / 20)

static const int TAMANHOS[] = { 1000, 10000, 100000 };
#define NUM_TAMANHOS (int)(sizeof TAMANHOS / sizeof TAMANHOS[0])

static const int BUBBLE_MEDIDOS[] = { 1000, 2000, 4000, 8000, 10000, 16000 };
#define NUM_BUBBLE (int)(sizeof BUBBLE_MEDIDOS / sizeof BUBBLE_MEDIDOS[0])

#define BUBBLE_MAX_MEDIDO 16000

static int cmp_preco_asc_qsort(const void *a, const void *b) {
    return cmp_preco_asc((const Produto *)a, (const Produto *)b);
}

static void run_bubble(Produto *v, int n) { bubblesort(v, n, cmp_preco_asc); }
static void run_quick (Produto *v, int n) { quicksort (v, n, cmp_preco_asc); }
static void run_qsort (Produto *v, int n) {
    qsort(v, (size_t)n, sizeof(Produto), cmp_preco_asc_qsort);
}

static void gerar(Produto *v, int n, unsigned semente) {
    srand(semente);
    for (int i = 0; i < n; i++) {
        v[i].id = i + 1;
        snprintf(v[i].nome, TAM_NOME, "Produto %d", i + 1);
        v[i].preco     = (float)(rand() % 1000000) / 100.0f;
        v[i].avaliacao = (float)(rand() % 51) / 10.0f;
        v[i].vendas    = rand() % 10000;
    }
}

static double medir_ms(const Produto *modelo, int n, void (*ordena)(Produto *, int)) {
    Produto *work = malloc((size_t)n * sizeof(Produto));
    if (work == NULL) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(1); }

    clock_t acumulado = 0;
    int execucoes = 0;
    while (acumulado < LIMIAR_CLOCKS) {
        memcpy(work, modelo, (size_t)n * sizeof(Produto));
        clock_t t0 = clock();
        ordena(work, n);
        clock_t t1 = clock();
        acumulado += (t1 - t0);
        execucoes++;
    }
    free(work);
    return (double)acumulado * 1000.0 / CLOCKS_PER_SEC / execucoes;
}

static double media_medicoes(int n, unsigned semente, int reps,
                             void (*ordena)(Produto *, int)) {
    Produto *modelo = malloc((size_t)n * sizeof(Produto));
    if (modelo == NULL) { fprintf(stderr, "Erro: memoria insuficiente\n"); exit(1); }
    double soma = 0;
    for (int r = 0; r < reps; r++) {
        gerar(modelo, n, semente + (unsigned)r);
        soma += medir_ms(modelo, n, ordena);
    }
    free(modelo);
    return soma / reps;
}

static int conferir_ordem_igual(int n, unsigned semente) {
    Produto *a = malloc((size_t)n * sizeof(Produto));
    Produto *b = malloc((size_t)n * sizeof(Produto));
    Produto *c = malloc((size_t)n * sizeof(Produto));
    if (!a || !b || !c) { free(a); free(b); free(c); return 0; }
    gerar(a, n, semente);
    memcpy(b, a, (size_t)n * sizeof(Produto));
    memcpy(c, a, (size_t)n * sizeof(Produto));
    run_bubble(a, n); run_quick(b, n); run_qsort(c, n);
    int iguais = 1;
    for (int i = 0; i < n; i++)
        if (a[i].id != b[i].id || a[i].id != c[i].id) { iguais = 0; break; }
    free(a); free(b); free(c);
    return iguais;
}

int main(int argc, char *argv[]) {
    int repeticoes = 3;
    unsigned semente = 42;
    if (argc >= 2) repeticoes = atoi(argv[1]);
    if (argc >= 3) semente = (unsigned)strtoul(argv[2], NULL, 10);
    if (repeticoes < 1) repeticoes = 1;

    printf("Benchmark de ordenacao (criterio: preco crescente)\n");
    printf("Repeticoes por tamanho: %d | semente base: %u\n\n", repeticoes, semente);
    fflush(stdout);

    if (!conferir_ordem_igual(5000, semente)) {
        fprintf(stderr, "ALERTA: os algoritmos divergiram na checagem de corretude!\n");
    } else {
        printf("Corretude: Bubble, Quick e qsort produzem a mesma ordem. OK\n\n");
    }

    double quick[NUM_TAMANHOS], qsort_[NUM_TAMANHOS];
    for (int t = 0; t < NUM_TAMANHOS; t++) {
        quick[t]  = media_medicoes(TAMANHOS[t], semente, repeticoes, run_quick);
        qsort_[t] = media_medicoes(TAMANHOS[t], semente, repeticoes, run_qsort);
        printf("  Quick/qsort em n=%d medidos\n", TAMANHOS[t]);
        fflush(stdout);
    }

    double num = 0, den = 0;
    double bubble_medido[NUM_BUBBLE];
    for (int i = 0; i < NUM_BUBBLE; i++) {
        int n = BUBBLE_MEDIDOS[i];
        bubble_medido[i] = media_medicoes(n, semente, repeticoes, run_bubble);
        double n2 = (double)n * (double)n;
        num += bubble_medido[i] * n2;
        den += n2 * n2;
        printf("  Bubble em n=%d medido (%.3f ms)\n", n, bubble_medido[i]);
        fflush(stdout);
    }
    double k = num / den;

    double bubble_tab[NUM_TAMANHOS];
    int bubble_estimado[NUM_TAMANHOS];
    for (int t = 0; t < NUM_TAMANHOS; t++) {
        int n = TAMANHOS[t];
        bubble_estimado[t] = 1;
        for (int i = 0; i < NUM_BUBBLE; i++) {
            if (BUBBLE_MEDIDOS[i] == n) { bubble_tab[t] = bubble_medido[i]; bubble_estimado[t] = 0; break; }
        }
        if (bubble_estimado[t]) bubble_tab[t] = k * (double)n * (double)n;
    }

    printf("\n### Resultados (media de %d execucoes, em ms)\n\n", repeticoes);
    printf("| n | Bubble Sort | Quick Sort | qsort (libc) |\n");
    printf("| --- | --- | --- | --- |\n");
    for (int t = 0; t < NUM_TAMANHOS; t++) {
        int n = TAMANHOS[t];
        char npt[16];
        if (n >= 1000) snprintf(npt, sizeof npt, "%d.%03d", n / 1000, n % 1000);
        else           snprintf(npt, sizeof npt, "%d", n);
        if (bubble_estimado[t])
            printf("| %s | %.1f* | %.3f | %.3f |\n", npt, bubble_tab[t], quick[t], qsort_[t]);
        else
            printf("| %s | %.3f | %.3f | %.3f |\n", npt, bubble_tab[t], quick[t], qsort_[t]);
    }
    printf("\n*estimado por extrapolacao O(n^2) (t = k*n^2, k = %.3e ms), ", k);
    printf("pois medir Bubble Sort a 100 mil na marra sobrecarrega a maquina.\n");

    FILE *csv = fopen("resultados.csv", "w");
    if (csv != NULL) {
        fprintf(csv, "n,algoritmo,ms,tipo\n");
        for (int i = 0; i < NUM_BUBBLE; i++)
            fprintf(csv, "%d,bubble,%.3f,medido\n", BUBBLE_MEDIDOS[i], bubble_medido[i]);
        for (int t = 0; t < NUM_TAMANHOS; t++) {
            if (bubble_estimado[t])
                fprintf(csv, "%d,bubble,%.3f,estimado\n", TAMANHOS[t], bubble_tab[t]);
            fprintf(csv, "%d,quick,%.3f,medido\n", TAMANHOS[t], quick[t]);
            fprintf(csv, "%d,qsort,%.3f,medido\n", TAMANHOS[t], qsort_[t]);
        }
        fclose(csv);
        printf("\nResultados salvos em resultados.csv\n");
    } else {
        fprintf(stderr, "Aviso: nao foi possivel escrever resultados.csv\n");
    }

    return 0;
}
